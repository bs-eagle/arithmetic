/**
 *       \file  binary_operators.h
 *      \brief  implementation of binary operators
 *     \author  Sergey Miryanov (sergey-miryanov), sergey.miryanov@gmail.com
 *       \date  23.10.2009
 *  \copyright  This source code is released under the terms of 
 *              the BSD License. See LICENSE for more details.
 * */
#ifndef BS_ARCH_BINARY_OPERATORS_H_
#define BS_ARCH_BINARY_OPERATORS_H_

#include "arithmetic_iface.h"
#include <cmath>

#include <boost/shared_ptr.hpp>

namespace blue_sky {
namespace arch {

  /**
   * \class binary_operator
   * \brief base class of binary operators
   *        inherits binary_operator_iface 
   */
  struct binary_operator : binary_operator_iface
  {
    /**
     * \brief  binary_operator ctor
     * \param  lhs lhs operand
     * \param  rhs rhs operand
     * \return 
     */
    binary_operator (const shared_operand_t &lhs, const shared_operand_t &rhs)
    : lhs (lhs)
    , rhs (rhs)
    {
    }

    shared_operand_t lhs; /**< @brief lhs operand */
    shared_operand_t rhs; /**< @brief rhs operand */
  };

  /**
   * \class max_operator
   * \brief incapsulates maximum (lhs, rhs) operation
   *        implements binary_operator_iface
   */
  struct max_operator : binary_operator
  {
    /**
     * \brief  max_operator ctor
     * \param  lhs lhs operand
     * \param  rhs rhs operand
     * \return 
     */
    max_operator (const shared_operand_t &lhs, const shared_operand_t &rhs)
    : binary_operator (lhs, rhs)
    {
    }
    /**
     * \brief  implements maximum (lhs[idx], rhs[idx]) operation
     * \param  idx value index
     * \return maximum of two values lhs[idx] and rhs[idx]
     */
    float16_t
    get (size_t idx) 
    {
      return (std::max) (lhs->get (idx), rhs->get (idx));
    }
  };

  /**
   * \class min_operator
   * \brief incapsulates minimum (lhs, rhs) operation
   *        implements binary_operator_iface
   */
  struct min_operator : binary_operator
  {
    /**
     * \brief  min_operator ctor
     * \param  lhs lhs operand
     * \param  rhs rhs operand
     * \return 
     */
    min_operator (const shared_operand_t &lhs, const shared_operand_t &rhs)
    : binary_operator (lhs, rhs)
    {
    }
    /**
     * \brief  implements minimum (lhs[idx], rhs[idx]) operation
     * \param  idx value index
     * \return minimum of two values lhs[idx] and rhs[idx]
     */
    float16_t
    get (size_t idx)
    {
      return (std::min) (lhs->get (idx), rhs->get (idx));
    }
  };

  /**
   * \class sum_operator
   * \brief incapsulates summation (lhs, rhs) operation
   *        implements binary_operator_iface
   */
  struct sum_operator : binary_operator
  {
    /**
     * \brief  sum_operator ctor
     * \param  lhs lhs operand
     * \param  rhs rhs operand
     * \return 
     */
    sum_operator (const shared_operand_t &lhs, const shared_operand_t &rhs)
    : binary_operator (lhs, rhs)
    {
    }
    /**
     * \brief  implements summation (lhs[idx], rhs[idx]) operation
     * \param  idx value index
     * \return sum of two values lhs[idx] and rhs[idx]
     */
    float16_t
    get (size_t idx)
    {
      return lhs->get (idx) + rhs->get (idx);
    }
  };
  /**
   * \class sub_operator
   * \brief incapsulates subtract (lhs, rhs) operation
   *        implements binary_operator_iface
   */
  struct sub_operator : binary_operator
  {
    /**
     * \brief  sub_operator ctor
     * \param  lhs lhs operand
     * \param  rhs rhs operand
     * \return 
     */
    sub_operator (const shared_operand_t &lhs, const shared_operand_t &rhs)
    : binary_operator (lhs, rhs)
    {
    }
    /**
     * \brief  implements subtract (lhs[idx], rhs[idx]) operation
     * \param  idx value index
     * \return sub of two values lhs[idx] and rhs[idx]
     */
    float16_t
    get (size_t idx)
    {
      return lhs->get (idx) - rhs->get (idx);
    }
  };
  /**
   * \class mul_operator
   * \brief incapsulates multiplication (lhs, rhs) operation
   *        implements binary_operator_iface
   */
  struct mul_operator : binary_operator
  {
    /**
     * \brief  mul_operator ctor
     * \param  lhs lhs operand
     * \param  rhs rhs operand
     * \return 
     */
    mul_operator (const shared_operand_t &lhs, const shared_operand_t &rhs)
    : binary_operator (lhs, rhs)
    {
    }
    /**
     * \brief  implements multiplication (lhs[idx], rhs[idx]) operation
     * \param  idx value index
     * \return mul of two values lhs[idx] and rhs[idx]
     */
    float16_t
    get (size_t idx)
    {
      return lhs->get (idx) * rhs->get (idx);
    }
  };
  /**
   * \class div_operator
   * \brief incapsulates division (lhs, rhs) operation
   *        implements binary_operator_iface
   */
  struct div_operator : binary_operator
  {
    /**
     * \brief  div_operator ctor
     * \param  lhs lhs operand
     * \param  rhs rhs operand
     * \return 
     */
    div_operator (const shared_operand_t &lhs, const shared_operand_t &rhs)
    : binary_operator (lhs, rhs)
    {
    }
    /**
     * \brief  implements division (lhs[idx], rhs[idx]) operation
     * \param  idx value index
     * \return div of two values lhs[idx] and rhs[idx]
     */
    float16_t
    get (size_t idx)
    {
      return lhs->get (idx) / rhs->get (idx);
    }
  };


} // namespace arch
} // namespace blue_sky

#endif // #ifndef BS_ARCH_BINARY_OPERATORS_H_

