/*
 *    Copyright (c) 2012-2013 Luxembourg University,
 *    Laboratory of Algorithmics, Cryptology and Security (LACS).
 *
 *    This file is part of the YAARX toolkit. YAARX stands for
 *    Yet Another ARX toolkit for analysis of ARX cryptographic algorithms.
 *
 *    YAARX is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    YAARX is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with YAARX.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * \file  max-adp-xor-fi-tests.cc 
 * \author V.Velichkov, vesselin.velichkov@uni.lu
 * \date 2012-2013
 * \brief Tests for max-adp-xor-fi.cc.
 */ 
#ifndef COMMON_H
#include "common.hh"
#endif
#ifndef ADP_XOR_FI_H
#include "adp-xor-fi.hh"
#endif
#ifndef MAX_ADP_XOR_FI_H
#include "max-adp-xor-fi.hh"
#endif

void test_max_adp_xor_fixed_input()
{
  printf("[%s:%d] Running test %s() ...\n", __FILE__, __LINE__, __FUNCTION__);
  gsl_matrix* A[2][2][2];
  adp_xor_fixed_input_alloc_matrices(A);
  adp_xor_fixed_input_sf(A);
  adp_xor_fixed_input_normalize_matrices(A);
  uint32_t a = xrandom() & MASK;
  uint32_t db = xrandom() & MASK;
  uint32_t dc = 0;
  double p1 = max_adp_xor_fixed_input(A, a, db, &dc);
  assert((p1 >= 0.0) && (p1 <= 1.0));
  double p2 = adp_xor_fixed_input(A, a, db, dc);
#if DEBUG_MAX_ADP_XOR_FI_TESTS
  printf("[%s:%d] ADP_XOR_FI_1[(%8X,%8X)->%8X] = %6.5f\n", 
			__FILE__, __LINE__, a, db, dc, p1);
  printf("[%s:%d] ADP_XOR_FI_2[(%8X,%8X)->%8X] = %6.5f\n", 
			__FILE__, __LINE__, a, db, dc, p2);
#endif  // #if DEBUG_MAX_ADP_XOR_FI_TESTS
  assert(p1 == p2);
  adp_xor_fixed_input_free_matrices(A);
  printf("[%s:%d] WORD_SIZE = %d. Test %s() OK.\n", __FILE__, __LINE__, WORD_SIZE, __FUNCTION__);
}

void test_max_adp_xor_fixed_input_is_max()
{
  printf("[%s:%d] Running test %s() ...\n", __FILE__, __LINE__, __FUNCTION__);
  gsl_matrix* A[2][2][2];
  adp_xor_fixed_input_alloc_matrices(A);
  adp_xor_fixed_input_sf(A);
  adp_xor_fixed_input_normalize_matrices(A);
  uint64_t N = (1ULL << WORD_SIZE);
  for(uint32_t a = 0; a < N; a++) {
	 for(uint32_t db = 0; db < N; db++) {
		uint32_t dc1 = 0;
		uint32_t dc2 = 0;
		double p1 = max_adp_xor_fixed_input(A, a, db, &dc1);
		assert((p1 >= 0.0) && (p1 <= 1.0));
		double p2 = max_adp_xor_fixed_input_exper(A, a, db, &dc2);
#if DEBUG_MAX_ADP_XOR_FI_TESTS
		printf("[%s:%d] ADP_XOR_FI_1[(%8X,%8X)->%8X] = %6.5f\n", 
				 __FILE__, __LINE__, a, db, dc1, p1);
		printf("[%s:%d] ADP_XOR_FI_2[(%8X,%8X)->%8X] = %6.5f\n", 
				 __FILE__, __LINE__, a, db, dc2, p2);
#endif  // #if DEBUG_MAX_ADP_XOR_FI_TESTS
		assert(p1 == p2);
	 }
  }
  adp_xor_fixed_input_free_matrices(A);
  printf("[%s:%d] WORD_SIZE = %d. Test %s() OK.\n", __FILE__, __LINE__, WORD_SIZE, __FUNCTION__);
}

int main()
{
  test_max_adp_xor_fixed_input();
  test_max_adp_xor_fixed_input_is_max();
  return 0;
}
