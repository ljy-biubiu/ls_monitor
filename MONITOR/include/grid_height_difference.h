
#ifndef PCL_FILTERS_VOXEL_GRID_HEIGHT_DIFFERENCE_H_
#define PCL_FILTERS_VOXEL_GRID_HEIGHT_DIFFERENCE_H_

#include <pcl/filters/boost.h>
#include <pcl/filters/filter.h>
#include <pcl/filters/filter_indices.h>

namespace pcl
{
    /** \brief GridHeightDifference assembles a local 2D grid over a given PointCloud, and downsamples the data.
      *
      * The GridHeightDifference class creates a *2D grid* over the input point cloud
      * data. Then, in each *cell* (i.e., 2D grid element), all the points
      * present will be *downsampled* with the minimum z value. This grid minimum
      * can be useful in a number of topographic processing tasks such as crudely
      * estimating ground returns, especially under foliage.
      *
      * \author Bradley J Chambers
      * \ingroup filters
      */
    template <typename PointT>
    class GridHeightDifference: public FilterIndices<PointT>
    {
    protected:
        using Filter<PointT>::filter_name_;
        using Filter<PointT>::getClassName;
        using Filter<PointT>::input_;
        using Filter<PointT>::indices_;

        typedef typename FilterIndices<PointT>::PointCloud PointCloud;

    public:
        /** \brief Empty constructor. */
        GridHeightDifference (const float resolution, const float difference_threshold)
        {
            setResolution (resolution);
            setDifferenceThreshold(difference_threshold);
            filter_name_ = "GridHeightDifference";
        }

        /** \brief Destructor. */
        virtual ~GridHeightDifference ()
        {
        }

        /** \brief Set the grid resolution.
          * \param[in] resolution the grid resolution
          */
        inline void
        setResolution (const float resolution)
        {
            resolution_ = resolution;
            // Use multiplications instead of divisions
            inverse_resolution_ = 1.0f / resolution_;
        }

        /** \brief Get the grid resolution. */
        inline float
        getResolution () { return (resolution_); }

        inline void
        setDifferenceThreshold (const float difference_threshold)
        {
            difference_threshold_ = difference_threshold;
        }

        /** \brief Get the grid difference_threshold. */
        inline float
        getDifferenceThreshold () { return (difference_threshold_); }

    protected:
        /** \brief The resolution. */
        float resolution_;

        /** \brief Internal resolution stored as 1/resolution_ for efficiency reasons. */
        float inverse_resolution_;

        float difference_threshold_;

        /** \brief Downsample a Point Cloud using a 2D grid approach
          * \param[out] output the resultant point cloud message
          */
        void
        applyFilter (PointCloud &output);

        /** \brief Filtered results are indexed by an indices array.
          * \param[out] indices The resultant indices.
          */
        void
        applyFilter (std::vector<int> &indices)
        {
            applyFilterIndices (indices);
        }

        /** \brief Filtered results are indexed by an indices array.
          * \param[out] indices The resultant indices.
          */
        void
        applyFilterIndices (std::vector<int> &indices);

    };
}

#ifdef PCL_NO_PRECOMPILE
#include "grid_height_difference.hpp"
#endif

#endif  //#ifndef PCL_FILTERS_VOXEL_GRID_HEIGHT_DIFFERENCE_H_