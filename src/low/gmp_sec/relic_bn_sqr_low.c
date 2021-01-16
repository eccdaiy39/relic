/*
 * RELIC is an Efficient LIbrary for Cryptography
 * Copyright (C) 2007-2020 RELIC Authors
 *
 * This file is part of RELIC. RELIC is legal property of its developers,
 * whose names are not listed here. Please refer to the COPYRIGHT file
 * for contact information.
 *
 * RELIC is free software; you can redistribute it and/or modify it under the
 * terms of the version 2.1 (or later) of the GNU Lesser General Public License
 * as published by the Free Software Foundation; or version 2.0 of the Apache
 * License as published by the Apache Software Foundation. See the LICENSE files
 * for more details.
 *
 * RELIC is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the LICENSE files for more details.
 *
 * You should have received a copy of the GNU Lesser General Public or the
 * Apache License along with RELIC. If not, see <https://www.gnu.org/licenses/>
 * or <https://www.apache.org/licenses/>.
 */

/**
 * @file
 *
 * Implementation of the multiple precision integer arithmetic multiplication
 * functions.
 *
 * @ingroup bn
 */

#include <gmp.h>

#include "relic_bn.h"
#include "relic_bn_low.h"
#include "relic_util.h"
#include "relic_alloc.h"

/*============================================================================*/
/* Public definitions                                                         */
/*============================================================================*/

dig_t bn_sqra_low(dig_t *c, const dig_t *a, int size) {
	dig_t carry, digit = a[0];

	carry = mpn_addmul_1(c, a, size, a[0]);
	mpn_add_1(c + size, c + size, size, carry);
	if (size > 1) {
		carry = mpn_addmul_1(c + 1, a + 1, size - 1, digit);
		return mpn_add_1(c + size, c + size, size, carry);
	}
	return 0;
}

void bn_sqrn_low(dig_t *c, const dig_t *a, int size) {
	dig_t *t = RLC_ALLOCA(dig_t, mpn_sec_sqr_itch(size));
	mpn_sec_sqr(c, a, size, t);
	RLC_FREE(t);
}
