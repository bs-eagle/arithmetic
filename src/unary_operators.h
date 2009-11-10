/**
 *       \file  unary_operators.h
 *      \brief  implementation of unary operators
 *     \author  Sergey Miryanov (sergey-miryanov), sergey.miryanov@gmail.com
 *       \date  23.10.2009
 *  \copyright  This source code is released under the terms of 
 *              the BSD License. See LICENSE for more details.
 * */
#ifndef BS_ARCH_UNARY_OPERATORS_H_
#define BS_ARCH_UNARY_OPERATORS_H_

#include "arithmetic_iface.h"

namespace blue_sky {
namespace arch {

  /**
   * \class unary_operator
   * \brief base class of unary operators 
   *        inherits unary_operator_iface
   */
  struct unary_operator : unary_operator_iface
  {
    /**
     * \brief  unary_operator ctor
     * \param  rhs rhs operand
     * \return 
     */
    unary_operator (const shared_operand_t &rhs)
    : rhs (rhs)
    {
    }

    boost::shared_ptr <operand_iface> rhs; /**< @brief rhs operand */
  };

  /**
   * \class unary_minus_operator
   * \brief incapsulates unary minus operation
   *        implements unary_operator_iface
   */
  struct unary_minus_operator : unary_operator
  {
    /**
     * \brief  unary_minus_operator ctor
     * \param  rhs rhs operand
     * \return 
     */
    unary_minus_operator (const shared_operand_t &rhs) 
    : unary_operator (rhs)
    {
    }

    /**
     * \brief  returns negated value of rhs[idx] value
     * \param  idx value index
     * \return negated value of rhs[idx]
     */
    float16_t
    get (size_t idx)
    {
      return -rhs->get (idx);
    }
  };


} // namespace arch
} // namespace blue_sky

#endif // #ifndef BS_ARCH_UNARY_OPERATORS_H_

