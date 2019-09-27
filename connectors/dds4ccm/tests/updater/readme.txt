This test verifies that the updater and the state listener function properly.

The sender has a list of assignments:
  1.  UPDATE_CREATE,
  2.  UPDATE_CREATE_ALREADY_EXIST,
  3.  UPDATE_ONE,
  4.  UPDATE_ONE_NOT_REGISTERED,
  5.  DELETE_ONE,
  6.  DELETE_ONE_NOT_REGISTERED,
  7.  UPDATE_DELETE_REGISTER,
  8.  CREATE_MANY,
  9.  UPDATE_MANY,
  10. DELETE_MANY,
  11. END_TEST

The receiver has two listeners (and therefor two DDS4CCM connectors):
  1. A one by one state listener (obo)
  2. A many by many state listener (mbm)

Both have the following methods:
  a. on_creation
  b. on_one_update
  c. on_many_updates
  d. on_deletion

The following table shows what the sender writes to DDS, and what the receiver should
receive in which listener.

Assignment                  | Sender            | Attempt to write | Sample(s) written | obo                      | mbm
===============================================================================================================================================
UPDATE_CREATE               | create_one        | {ONE_1,1}        | + {ONE_1,1}       | on_creation {ONE_1,1}    | on_creation {ONE_1,1}
-----------------------------------------------------------------------------------------------------------------------------------------------
UPDATE_CREATE_ALREADY_EXIST | create_one        | {ONE_1,1}        | NONE              | NONE                     | NONE
-----------------------------------------------------------------------------------------------------------------------------------------------
UPDATE_ONE                  | update_one        | {ONE_1,6}        | {ONE_1,6}         | on_one_update {ONE_1,6}  | on_many_updates {ONE_1,6}
-----------------------------------------------------------------------------------------------------------------------------------------------
UPDATE_ONE_NOT_REGISTERED   | update_one        | {ONE_2,2}        | NONE              | NONE                     | NONE
-----------------------------------------------------------------------------------------------------------------------------------------------
DELETE_ONE                  | delete_one        | {ONE_1,6}        | - {ONE_1,6}       | on_deletion              | on_deletion
-----------------------------------------------------------------------------------------------------------------------------------------------
UPDATE_DELETE_REGISTER      | delete_one        | {ONE_2,2}        | NONE              | NONE                     | NONE
-----------------------------------------------------------------------------------------------------------------------------------------------
DELETE_ONE_NOT_REGISTERED   | register_instance | {ONE_3,3}        | + {ONE_3,3}       | NONE                     | NONE
                            | update_one        | {ONE_3,8}        | {ONE_3,8}         | on_creation {ONE_3,8}    | on_creation {ONE_3,8}
                            | update_one        | {ONE_2,2}*       | NONE              | NONE                     | NONE
                            | delete_one        | {ONE_3,3}        | - {ONE_3,3}       | on_deletion              | on_deletion
-----------------------------------------------------------------------------------------------------------------------------------------------
CREATE_MANY                 | create_many       | {MANY_1,1}       | + {MANY_1,1}      | on_creation {MANY_1,1}   | on_creation {MANY_1,1}
                            |                   | {MANY_2,2}       | + {MANY_2,2}      | on_creation {MANY_2,2}   | on_creation {MANY_2,2}
                            |                   | {MANY_3,3}       | + {MANY_3,3}      | on_creation {MANY_3,3}   | on_creation {MANY_3,3}
                            | create_many**     | {MANY_1,1}       | NONE              | NONE                     | NONE
                            |                   | {ZZZ_2,2}        | NONE              | NONE                     | NONE
                            |                   | {MANY_3,3}       | NONE              | NONE                     | NONE
-----------------------------------------------------------------------------------------------------------------------------------------------
UPDATE_MANY                 | update_many       | {MANY_1,6}       | {MANY_1,6}        | on_one_update {MANY_1,6} | on_many_updates {MANY_1,6},
                            |                   | {MANY_2,7}       | {MANY_2,7}        | on_one_update {MANY_2,7} |                 {MANY_2,7},
                            |                   | {MANY_3,8}       | {MANY_3,8}        | on_one_update {MANY_3,8} |                 {MANY_3,8}
                            | update_many***    | {MANY_1,6}       | NONE              | NONE                     | NONE
                            |                   | {XXX_1,1}        | NONE              | NONE                     | NONE
                            |                   | {XXX_2,2}        | NONE              | NONE                     | NONE
-----------------------------------------------------------------------------------------------------------------------------------------------
DELETE_MANY                 | delete_many***    | {MANY_1,6}       | NONE              | NONE                     | NONE
                            |                   | {XXX_1,1}        | NONE              | NONE                     | NONE
                            |                   | {XXX_2,2}        | NONE              | NONE                     | NONE
                            | delete_many       | {MANY_1,1}       | - {MANY_1,1}      | on_deletion              | on_deletion
                            |                   | {MANY_2,2}       | - {MANY_2,2}      | on_deletion              | on_deletion
                            |                   | {MANY_3,3}       | - {MANY_3,3}      | on_deletion              | on_deletion
-----------------------------------------------------------------------------------------------------------------------------------------------

*   : incorrect instance handle used.
**  : Testing the 'AlreadyExist' exception
*** : Testing the 'NonExistent' exception
