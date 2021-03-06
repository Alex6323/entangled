/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/entangled
 *
 * Refer to the LICENSE file for licensing information
 */

#include <unity/unity.h>

#include "ciri/api/api.h"
#include "ciri/api/tests/defs.h"
#include "gossip/node.h"

static iota_api_t api;
static node_t node;

void test_get_tips(void) {
  get_tips_res_t *res = get_tips_res_new();
  flex_trit_t hashes[10][243];
  tryte_t trytes[81] =
      "A99999999999999999999999999999999999999999999999999999999999999999999999"
      "999999999";

  for (size_t i = 0; i < 10; i++) {
    flex_trits_from_trytes(hashes[i], HASH_LENGTH_TRIT, trytes,
                           HASH_LENGTH_TRYTE, HASH_LENGTH_TRYTE);
    trytes[0]++;
  }

  TEST_ASSERT(tips_cache_init(&node.tips, 5) == RC_OK);

  TEST_ASSERT(tips_cache_add(&node.tips, hashes[5]) == RC_OK);
  TEST_ASSERT(tips_cache_add(&node.tips, hashes[6]) == RC_OK);
  TEST_ASSERT(tips_cache_add(&node.tips, hashes[7]) == RC_OK);
  TEST_ASSERT(tips_cache_add(&node.tips, hashes[8]) == RC_OK);
  TEST_ASSERT(tips_cache_add(&node.tips, hashes[9]) == RC_OK);

  TEST_ASSERT(tips_cache_set_solid(&node.tips, hashes[5]) == RC_OK);
  TEST_ASSERT(tips_cache_set_solid(&node.tips, hashes[6]) == RC_OK);
  TEST_ASSERT(tips_cache_set_solid(&node.tips, hashes[7]) == RC_OK);
  TEST_ASSERT(tips_cache_set_solid(&node.tips, hashes[8]) == RC_OK);
  TEST_ASSERT(tips_cache_set_solid(&node.tips, hashes[9]) == RC_OK);

  TEST_ASSERT(tips_cache_add(&node.tips, hashes[0]) == RC_OK);
  TEST_ASSERT(tips_cache_add(&node.tips, hashes[1]) == RC_OK);
  TEST_ASSERT(tips_cache_add(&node.tips, hashes[2]) == RC_OK);
  TEST_ASSERT(tips_cache_add(&node.tips, hashes[3]) == RC_OK);
  TEST_ASSERT(tips_cache_add(&node.tips, hashes[4]) == RC_OK);

  TEST_ASSERT(iota_api_get_tips(&api, res) == RC_OK);
  TEST_ASSERT_EQUAL_INT(get_tips_res_tip_num(res), 10);

  for (size_t i = 0; i < 10; i++) {
    trit_array_p trit_array = get_tips_res_tip_at(res, i);
    TEST_ASSERT_EQUAL_INT(
        memcmp(trit_array->trits, hashes[i], FLEX_TRIT_SIZE_243), 0);
  }

  TEST_ASSERT(tips_cache_destroy(&node.tips) == RC_OK);

  get_tips_res_free(res);
}

int main(void) {
  UNITY_BEGIN();

  api.node = &node;

  RUN_TEST(test_get_tips);

  return UNITY_END();
}
