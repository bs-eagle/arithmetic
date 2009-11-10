/**
 *       \file  arithmetic_iface.h
 *      \brief  base interface for arithmetic stuff
 *     \author  Sergey Miryanov (sergey-miryanov), sergey.miryanov@gmail.com
 *       \date  23.10.2009
 *  \copyright  This source code is released under the terms of 
 *              the BSD License. See LICENSE for more details.
 * */
#ifndef BS_ARCH_ARITHMETIC_IFACE_H_
#define BS_ARCH_ARITHMETIC_IFACE_H_

#include "shared_vector.h"
#include <boost/shared_ptr.hpp>

namespace blue_sky {
namespace arch {

  /**
   * \class operand_iface
   * \brief base interface for arithmetic operands
   */
  struct operand_iface
  {
    virtual ~operand_iface () {}

    /**
     * \brief  returns value with index
     * \param  idx is an index of value
     * \return 
     */
    virtual float16_t
    get (size_t idx) = 0;
  };

  /**
   * \type shared_operand_t
   * \brief typedef for boost::shared_ptr <operand_iface>
   */
  typedef boost::shared_ptr <operand_iface> shared_operand_t;

  /**
   * \class unary_operator_iface
   * \brief base interface for unary operators
   */
  struct unary_operator_iface : operand_iface
  {
  };

  /**
   * \class binary_operator_iface
   * \brief base interface for binary operators
   */
  struct binary_operator_iface : operand_iface
  {
  };

  /**
   * \class array_operand_iface
   * \brief base interface for array operand
   * \detail implementor should implement get 
   *         function that returns array[idx] 
   *         value
   */
  struct array_operand_iface : operand_iface
  {
  };

  /**
   * \class float_operand_iface
   * \brief base interface for float operand
   * \detail implementor should implement get
   *         function that returns value with
   *         object was created
   */
  struct float_operand_iface : operand_iface
  {
  };

  /**
   * \class slice
   * \brief class for store information about data slice
   * \detail arithmetic will iterate through data in region
   *         that specified by slice
   */
  struct slice
  {
    struct point
    {
      long long begin; /**< @brief begin of point */
      long long end;  /**< @brief end of point */

      /**
       * \brief  point constructor
       * \param  begin begin of point
       * \param  end end of point
       * \return 
       */
      point (long long begin, long long end)
      : begin (begin), end (end)
      {
      }
    };

    /**
     * \brief  slice constructor
     * \param  x i coord for slice
     * \param  y j coord for slice
     * \param  z k coord for slice
     * \return 
     */
    slice (const point &x, const point &y, const point &z)
    : x (x), y (y), z (z)
    {
    }

    point x; /**< @brief i coord of slice */
    point y; /**< @brief j coord of slice */
    point z; /**< @brief k coord of slice */
  };

  /**
   * \class arithmetic_iface
   * \brief base interface for arithmetic processor
   */
  struct arithmetic_iface
  {
    /**
     * \brief  arithmetic_iface destructor
     */
    virtual ~arithmetic_iface () {}

    /**
     * \brief  process arithmetic expression
     * \param  line string with arithmetic expression
     * \return 
     */
    virtual void
    process_line (const std::string &line) = 0;
  };

  /**
   * \type shared_arithmetic_t
   * \brief typedef for boost::shared_ptr <arithmetic_iface>
   */
  typedef boost::shared_ptr <arithmetic_iface> shared_arithmetic_t;

} // namespace arch
} // namespace blue_sky

#endif // #ifndef BS_ARCH_ARITHMETIC_IFACE_H_

