//  Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under the BSD-style license found in the
//  LICENSE file in the root directory of this source tree. An additional grant
//  of patent rights can be found in the PATENTS file in the same directory.
//
// The following only applies to changes made to this file as part of YugaByte development.
//
// Portions Copyright (c) YugaByte, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
// in compliance with the License.  You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software distributed under the License
// is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
// or implied.  See the License for the specific language governing permissions and limitations
// under the License.
//

#include "yb/util/flags.h"
#include "yb/docdb/docdb_rocksdb_util.h"
#include "yb/rocksdb/convenience.h"
#include "yb/rocksdb/db_dump_tool.h"
#include "yb/tablet/tablet_options.h"

DEFINE_UNKNOWN_string(db_path, "", "Path to the db that will be dumped");
DEFINE_UNKNOWN_string(dump_location, "", "Path to where the dump file location");
DEFINE_UNKNOWN_bool(anonymous, false,
            "Remove information like db path, creation time from dumped file");
DEFINE_UNKNOWN_string(db_options, "",
              "Options string used to open the database that will be dumped");

int main(int argc, char** argv) {
  GFLAGS::ParseCommandLineFlags(&argc, &argv, true);

  if (FLAGS_db_path == "" || FLAGS_dump_location == "") {
    fprintf(stderr, "Please set --db_path and --dump_location\n");
    return 1;
  }

  rocksdb::DumpOptions dump_options;
  dump_options.db_path = FLAGS_db_path;
  dump_options.dump_location = FLAGS_dump_location;
  dump_options.anonymous = FLAGS_anonymous;

  rocksdb::Options db_options;
  if (FLAGS_db_options != "") {
    rocksdb::Options parsed_options;
    rocksdb::Status s = rocksdb::GetOptionsFromString(
        db_options, FLAGS_db_options, &parsed_options);
    if (!s.ok()) {
      fprintf(stderr, "Cannot parse provided db_options\n");
      return 1;
    }
    db_options = parsed_options;
  }

  yb::tablet::TabletOptions t_options;
  yb::docdb::InitRocksDBOptions(
      &db_options, "" /* log_prefix */, nullptr /* statistics */, t_options);

  rocksdb::DbDumpTool tool;
  if (!tool.Run(dump_options, db_options)) {
    return 1;
  }
  return 0;
}
