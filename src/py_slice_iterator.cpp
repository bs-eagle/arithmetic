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

#include "rs_mesh_iface.h"
#include "rs_smesh_iface.h"

#include "strategies.h"
#include "aligned_allocator.h"
#include "export_python_wrapper.h"

using namespace blue_sky::python;
using namespace boost::python;

namespace blue_sky {
namespace arch {
namespace python {

  /**
   * \brief  generalized version of iterate_slice
   * \detail iterates through data in slice range, 
   *         evaluates expression top and stores result 
   *         of it in dest array
   * \param  s slice that stores info of data range
   * \param  dest destination array, result of 
   *              expression will be stored in this array
   * \param  top top of the expression tree, expression 
   *             will be evaluated from top to bottom of 
   *             tree
   * \param  __formal used to deduce template type for index_t
   * \return 
   * */
  template <typename array_t, typename index_t>
  void
  iterate_slice_t (const slice &s, array_t &dest, const shared_operand_t &top, index_t)
  {
    BS_ASSERT (dest.size () >= s.x.end * s.y.end * s.z.end) (s.x.end) (s.y.end) (s.z.end);

    index_t idx = 0;
    for (index_t i = s.x.begin; i < s.x.end + 1; ++i)
      {
        for (index_t j = s.y.begin; j < s.y.end + 1; ++j)
          {
            for (index_t k = s.z.begin; k < s.z.end + 1; ++k, ++idx)
              {
                dest [idx] = top->get (idx);
              }
          }
      }
  }

  template <typename strategy_t>
  void
  py_slice_iterator <strategy_t>::iterate_slice_float (const slice &s,
    array_float16_t &dest, const shared_operand_t &top)
  {
    typedef typename strategy_t::index_t index_t;
    iterate_slice_t (s, dest, top, index_t ());
  }

  template <typename strategy_t>
  void
  py_slice_iterator <strategy_t>::iterate_slice_int (const slice &s,
    array_uint8_t &dest, const shared_operand_t &top)
  {
    typedef typename strategy_t::index_t index_t;
    iterate_slice_t (s, dest, top, index_t ());
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

    strategy_exporter::export_base_ext <py_slice_iterator, py_slice_iterator_exporter, class_type::concrete_class> ("slice_iterator");
  }

} // namespace python
} // namespace arch
} // namespace blue_sky

