/**
 *       \file  py_slice_iterator.h
 *      \brief  Export to python slice and slice_iterator
 *     \author  Sergey Miryanov (sergey-miryanov), sergey.miryanov@gmail.com
 *       \date  26.10.2009
 *  \copyright  This source code is released under the terms of 
 *              the BSD License. See LICENSE for more details.
 * */
#ifndef BS_ARCH_PY_SLICE_ITERATOR_H_
#define BS_ARCH_PY_SLICE_ITERATOR_H_

#include "arithmetic_iface.h"
#include "data_dimens.h"

namespace blue_sky {
namespace arch {
namespace python {

  /**
   * \class py_slice_iterator 
   * \brief Incapsulates arithmetic expression evaluation 
   * */
  struct py_slice_iterator 
  {
    /**
     * \brief  Iterates through data in slice range, 
     *         evaluates expression top and stores result 
     *         of it in float dest array
     * \param  s Slice that stores info of data range
     * \param  dimens Stores data dimensions
     * \param  dest Destination array, result of 
     *              expression will be stored in this array
     * \param  top Top of the expression tree, expression 
     *             will be evaluated from top to bottom of 
     *             tree
     * */
    void
    iterate_slice_float (const slice &s, const data_dimens &dimens, array_float16_t &dest, const shared_operand_t &top);

    /**
     * \brief  Iterates through data in slice range, 
     *         evaluates expression top and stores result 
     *         of it in integer dest array
     * \param  s Slice that stores info of data range
     * \param  dimens Stores data dimensions
     * \param  dest Destination array, result of 
     *              expression will be stored in this array
     * \param  top Top of the expression tree, expression 
     *             will be evaluated from top to bottom of 
     *             tree
     * */
    void
    iterate_slice_int (const slice &s, const data_dimens &dimens, array_uint8_t &dest, const shared_operand_t &top);
  };

  /**
   * \brief  Exports python wrappers for slice and py_slice_iterator
   * */
  void
  export_slice_iterator ();

} // namespace python
} // namespace arch
} // namespace blue_sky

#endif // #ifndef BS_ARCH_PY_SLICE_ITERATOR_H_

