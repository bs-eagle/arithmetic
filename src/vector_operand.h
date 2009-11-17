#ifndef BS_ARCH_VECTOR_OPERAND_H_
#define BS_ARCH_VECTOR_OPERAND_H_

#include "arithmetic_iface.h"

namespace blue_sky {
namespace arch {

  /**
   * \class vector_operand
   * \brief Implementation of vector operand
   */
  struct vector_operand : array_operand_iface
  {
    /**
     * \brief  vector_operand constructor
     * \param  array handled array
     */
    vector_operand (const array_float16_t &array)
    : array (array)
    {
    }

    /**
     * \brief  returns array[idx] value
     * \param  __formal
     * \param  local_idx value index
     * \return array[idx] value
     */
    float16_t
    get (long long, long long local_idx)
    {
      if (local_idx >= static_cast <long long> (array.size ()))
        {
          return 0;
        }

      return array[local_idx];
    }

    array_float16_t array; /**< @brief handled array */
  };

} // namespace arch
} // namespace blue_sky

#endif // #ifndef BS_ARCH_VECTOR_OPERAND_H_

