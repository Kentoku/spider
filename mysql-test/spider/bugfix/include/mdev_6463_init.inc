--disable_warnings
--disable_query_log
--disable_result_log
--source ../t/test_init.inc
--source ../t/ha_test_init.inc
if (!$HAVE_PARTITION)
{
  --source mdev_6463_deinit.inc
  --enable_result_log
  --enable_query_log
  --enable_warnings
  skip Test requires partitioning;
}
--enable_result_log
--enable_query_log
--enable_warnings
let $MASTER_1_COMMENT_HA_P_2_1=
  PARTITION BY KEY(a) (
    PARTITION pt1 COMMENT='srv "s_2_1 s_2_2", tbl "ta_r ta_r3",
    msi "$CHILD3_1_SERVER_ID", mkd "2", priority "1000"',
    PARTITION pt2 COMMENT='srv "s_2_1 s_2_3", tbl "ta_r2 ta_r4",
    msi "$CHILD3_1_SERVER_ID", mkd "2", priority "1000001"'
  );
let $MASTER_1_SET_RECOVERY_STATUS_P_2_1=
  ALTER TABLE ta_l2
  PARTITION BY KEY(a) (
    PARTITION pt1 COMMENT='srv "s_2_1 s_2_2", tbl "ta_r ta_r3",
    msi "$CHILD3_1_SERVER_ID", mkd "2", priority "1000", lst "2 0"',
    PARTITION pt2 COMMENT='srv "s_2_1 s_2_3", tbl "ta_r2 ta_r4",
    msi "$CHILD3_1_SERVER_ID", mkd "2", priority "1000001"'
  );
let $MASTER_1_SET_OK_STATUS_P_2_1=
  ALTER TABLE ta_l2
  PARTITION BY KEY(a) (
    PARTITION pt1 COMMENT='srv "s_2_1 s_2_2", tbl "ta_r ta_r3",
    msi "$CHILD3_1_SERVER_ID", mkd "2", priority "1000", lst "1 0"',
    PARTITION pt2 COMMENT='srv "s_2_1 s_2_3", tbl "ta_r2 ta_r4",
    msi "$CHILD3_1_SERVER_ID", mkd "2", priority "1000001"'
  );
let $MASTER_1_COPY_TABLES_P_2_1=
  SELECT spider_copy_tables('ta_l2#P#pt1', '1', '0');
