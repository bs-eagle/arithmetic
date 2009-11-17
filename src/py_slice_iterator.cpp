/**
 *       \file  py_slice_iterator.cpp
 *      \brief  implementation of python wrapper for slice_iterator
 *     \author  Sergey Miryanov (sergey-miryanov), sergey.miryanov@gmail.com
 *       \date  26.10.2009
 *  \copyright  This source code is released under the terms of 
 *              the BSD License. See LICENSE for more details.
 * */
#include "bs_assert.h"
#include "bs_common.h"
#include "bs_kernel.h"
#include "bs_object_base.h"
#include <boost/array.hpp>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

#include "py_slice_iterator.h"

#include "strategies.h"
#include "aligned_allocator.h"
#include "export_python_wrapper.h"

using namespace blue_sky::python;
using namespace boost::python;

namespace blue_sky {
namespace arch {
namespace python {

  /**
   * \brief   Generalized version of iterate_slice
   * \details Iterates through data in slice range, 
   *          evaluates expression top and stores result 
   *          of it in dest array
   * \param  s Slice that stores info of data range
   * \param  dimens Holds data dimensions
   * \param  dest Destination array, result of 
   *              expression will be stored in this array
   * \param  top Top of the expression tree, expression 
   *             will be evaluated from top to bottom 
   * */
  template <typename array_t>
  void
  iterate_slice_t (const slice &s, const data_dimens &dimens, array_t &dest, const shared_operand_t &top)
  {
    typedef long long index_t;

    index_t sx = s.x.end - s.x.begin;
    index_t sy = s.y.end - s.y.begin;
    index_t sz = s.z.end - s.z.begin;

    if (sx < 0 || sx >= dimens.nx || s.x.end > dimens.nx)
      bs_throw_exception (boost::format ("Invalid slice.x (%ld, %ld), dimens.nx = %ld") % s.x.begin % s.x.end % dimens.nx);

    if (sy < 0 || sy >= dimens.ny || s.y.end > dimens.ny)
      bs_throw_exception (boost::format ("Invalid slice.y (%ld, %ld), dimens.ny = %ld") % s.y.begin % s.y.end % dimens.ny);

    if (sz < 0 || sz >= dimens.nz || s.z.end > dimens.nz)
      bs_throw_exception (boost::format ("Invalid slice.z (%ld, %ld), dimens.nz = %ld") % s.z.begin % s.z.end % dimens.nz);

    if (sx * sy * sz >= static_cast <index_t> (dest.size ()))
      bs_throw_exception (boost::format ("Invalid dest size (%ld), slice (%ld:%ld, %ld:%ld, %ld:%ld)") % dest.size () % s.x.begin 
        % s.x.end % s.y.begin % s.y.end % s.z.begin % s.z.end);

    index_t global_idx = s.x.begin * dimens.nx * dimens.ny + s.y.begin * dimens.ny + s.z.begin;
    index_t local_idx = 0;
    for (index_t i = s.x.begin; i < s.x.end + 1; ++i)
      {
        for (index_t j = s.y.begin; j < s.y.end + 1; ++j)
          {
            for (index_t k = s.z.begin; k < s.z.end + 1; ++k, ++global_idx, ++local_idx)
              {
                dest [global_idx] = top->get (global_idx, local_idx);
              }
          }
      }
  }

  void
  py_slice_iterator::iterate_slice_float (const slice &s, const data_dimens &dimens,
    array_float16_t &dest, const shared_operand_t &top)
  {
    iterate_slice_t (s, dimens, dest, top);
  }

  void
  py_slice_iterator::iterate_slice_int (const slice &s, const data_dimens &dimens,
    array_uint8_t &dest, const shared_operand_t &top)
  {
    iterate_slice_t (s, dimens, dest, top);
  }

  /**
   * \class py_slice_iterator_exporter
   * \brief boost::python exporter, class_exporter framework 
   *        uses this exporter to export class to python
   * */
  PY_EXPORTER (py_slice_iterator_exporter, empty_exporter)
    .def ("iterate_slice", &T::iterate_slice_float)
    .def ("iterate_slice", &T::iterate_slice_int)
  PY_EXPORTER_END;

  void
  export_slice_iterator ()
  {
    class_ <slice::point> ("slice_point", init <long long, long long> ())
      .add_property ("begin", &slice::point::begin)
      .add_property ("end", &slice::point::end)
      ;
    class_ <slice> ("slice", init <const slice::point &, const slice::point &, const slice::point &> ())
      .add_property ("x", &slice::x)
      .add_property ("y", &slice::y)
      .add_property ("z", &slice::z)
      ;

    base_exporter <py_slice_iterator, py_slice_iterator_exporter, class_type::concrete_class>::export_class ("slice_iterator");
  }

} // namespace python
} // namespace arch
} // namespace blue_sky

