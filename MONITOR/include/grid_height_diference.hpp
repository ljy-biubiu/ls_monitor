#ifndef PCL_FILTERS_IMPL_VOXEL_GRID_HEIGHT_DIFFERENCE_H_
#define PCL_FILTERS_IMPL_VOXEL_GRID_HEIGHT_DIFFERENCE_H_

#include <pcl/common/common.h>
#include <pcl/common/io.h>
#include "grid_height_difference.h"

struct point_index_idx
{
    unsigned int idx;
    unsigned int cloud_point_index;

    point_index_idx (unsigned int idx_, unsigned int cloud_point_index_) : idx (idx_), cloud_point_index (cloud_point_index_) {}
    bool operator < (const point_index_idx &p) const { return (idx < p.idx); }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT> void
pcl::GridHeightDifference<PointT>::applyFilter (PointCloud &output)
{
    // Has the input dataset been set already?
    if (!input_)
    {
        PCL_WARN ("[pcl::%s::applyFilter] No input dataset given!\n", getClassName ().c_str ());
        output.width = output.height = 0;
        output.points.clear ();
        return;
    }

    std::vector<int> indices;

    output.is_dense = true;
    applyFilterIndices (indices);
    pcl::copyPointCloud<PointT> (*input_, indices, output);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT> void
pcl::GridHeightDifference<PointT>::applyFilterIndices (std::vector<int> &indices)
{
//    std::cout << "************************Inter Grid Height Difference ************************" << std::endl;
//    std::cout << "indices before resize:" << indices.size() << std::endl;
    indices.resize (indices_->size ());
//    std::cout << "indices before size:" << indices.size() << std::endl;
    int oii = 0;

    // Get the minimum and maximum dimensions
    Eigen::Vector4f min_p, max_p;
    getMinMax3D<PointT> (*input_, *indices_, min_p, max_p);

    // Check that the resolution is not too small, given the size of the data
    std::int64_t dx = static_cast<std::int64_t> ((max_p[0] - min_p[0]) * inverse_resolution_)+1;
    std::int64_t dy = static_cast<std::int64_t> ((max_p[1] - min_p[1]) * inverse_resolution_)+1;

    if ((dx*dy) > static_cast<std::int64_t> (std::numeric_limits<std::int32_t>::max ()))
    {
        PCL_WARN ("[pcl::%s::applyFilter] Leaf size is too small for the input dataset. Integer indices would overflow.\n", getClassName ().c_str ());
        return;
    }

    Eigen::Vector4i min_b, max_b, div_b, divb_mul;

    // Compute the minimum and maximum bounding box values
    min_b[0] = static_cast<int> (std::floor (min_p[0] * inverse_resolution_));
    max_b[0] = static_cast<int> (std::floor (max_p[0] * inverse_resolution_));
    min_b[1] = static_cast<int> (std::floor (min_p[1] * inverse_resolution_));
    max_b[1] = static_cast<int> (std::floor (max_p[1] * inverse_resolution_));

    // Compute the number of divisions needed along all axis
    div_b = max_b - min_b + Eigen::Vector4i::Ones ();
    div_b[3] = 0;

    // Set up the division multiplier
    divb_mul = Eigen::Vector4i (1, div_b[0], 0, 0);

    std::vector<point_index_idx> index_vector;
    index_vector.reserve (indices_->size ());

    // First pass: go over all points and insert them into the index_vector vector
    // with calculated idx. Points with the same idx value will contribute to the
    // same point of resulting CloudPoint
    for (const auto& index : (*indices_))
    {
        if (!input_->is_dense)
            // Check if the point is invalid
            if (!pcl_isfinite ((*input_)[index].x) ||
                !pcl_isfinite ((*input_)[index].y) ||
                !pcl_isfinite ((*input_)[index].z))
                continue;

        int ijk0 = static_cast<int> (std::floor ((*input_)[index].x * inverse_resolution_) - static_cast<float> (min_b[0]));
        int ijk1 = static_cast<int> (std::floor ((*input_)[index].y * inverse_resolution_) - static_cast<float> (min_b[1]));

        // Compute the grid cell index
        // TODO:wu 20220414 以下公式是将栅格化的二维索引转成向量化的一维索引，即是每行拼接到前一行的末尾。divb_mul[0]为1，divb_mul[1]为div_b[0]
        // |[ ] [ ] [ ] [ ] [ ] [ ]|
        // |[ ] [ ] [ ] [*] [ ] [ ]| >>>>> |[ ] [ ] [ ] [ ] [ ] [ ]||[ ] [ ] [ ] [*] [ ] [ ]||[ ] [ ] [ ] [ ] [ ] [ ]|
        // |[ ] [ ] [ ] [ ] [ ] [ ]|
        int idx = ijk0 * divb_mul[0] + ijk1 * divb_mul[1];
        index_vector.emplace_back(static_cast<unsigned int> (idx), index);
    }

    // Second pass: sort the index_vector vector using value representing target cell as index
    // in effect all points belonging to the same output cell will be next to each other
    // 使用表示目标单元格的值作为索引,对 index_vector 进行排序，实际上属于同一个输出单元格的所有点都将挨在一起
    // less<T>变成升序（从左到右遍历下标时，数组元素是从小到大）
    // greater<T>变成降序（从左到右遍历下标时，数组元素是从大到小）
    std::sort (index_vector.begin (), index_vector.end (), std::less<point_index_idx> ());

    // Third pass: count output cells
    // we need to skip all the same, adjacenent idx values
    unsigned int total = 0;
    unsigned int index = 0;

    // first_and_last_indices_vector[i] represents the index in index_vector of the first point in
    // index_vector belonging to the voxel which corresponds to the i-th output point,
    // and of the first point not belonging to.
    std::vector<std::pair<unsigned int, unsigned int> > first_and_last_indices_vector;

    // Worst case size
    first_and_last_indices_vector.reserve (index_vector.size ());
    while (index < index_vector.size ())
    {
        unsigned int i = index + 1;
        while (i < index_vector.size () && index_vector[i].idx == index_vector[index].idx)
            ++i;
        ++total; //表示有点的栅格个数
        first_and_last_indices_vector.emplace_back(index, i);// index表示位于同一个栅格里面的第1个点序号，i表示位于同一个栅格里面的最后点的序号，
        // 每个栅格各自所包含点的首末序号，就可以迭代比较每个栅格点的局部最小值和最大值
        index = i;
    }

    // Fourth pass: locate grid minimums
    indices.resize (total);
    // TODO:WU
//    indices.resize (indices_->size ());
    index = 0;
    std::vector<int> difference_indices;
    difference_indices.resize(index_vector.size());
    for (const auto &cp : first_and_last_indices_vector)
    {
        unsigned int first_index = cp.first;
        unsigned int last_index = cp.second;
        unsigned int min_index = index_vector[first_index].cloud_point_index;
        float min_z = (*input_)[index_vector[first_index].cloud_point_index].z;

        // TODO:WU
        unsigned int difference_index = 0;
        float difference_z = 0;

        for (unsigned int i = first_index + 1; i < last_index; ++i)
        {
            if ((*input_)[index_vector[i].cloud_point_index].z < min_z)
            {
                min_z = (*input_)[index_vector[i].cloud_point_index].z;
                min_index = index_vector[i].cloud_point_index;
            }
        }

        // TODO:WU
        for (unsigned int i = first_index + 1; i < last_index; ++i)
        {
            difference_z = (*input_)[index_vector[i].cloud_point_index].z - min_z;
            if (difference_z > difference_threshold_)
            {
                difference_indices[index] = index_vector[i].cloud_point_index;
                ++index;
            }
        }

//        indices[index] = min_index;
//        ++index;
    }
    difference_indices.resize(index);
    oii = indices.size ();

    // Resize the output arrays
    indices.resize (index);
    indices = difference_indices;
//    std::cout << "total size:" << total << std::endl;
//    std::cout << "indices after  difference size:" << indices.size () << std::endl;
}

#define PCL_INSTANTIATE_GridHeightDifference(T) template class PCL_EXPORTS pcl::GridHeightDifference<T>;

#endif    // PCL_FILTERS_IMPL_VOXEL_GRID_HEIGHT_DIFFERENCE_H_

