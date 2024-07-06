#include <iostream>
#include <string>

#include "leveldb/cache.h"
#include "leveldb/comparator.h"
#include "leveldb/db.h"
#include "leveldb/env.h"
#include "leveldb/filter_policy.h"
#include "leveldb/write_batch.h"
#include "port/port.h"
#include "util/crc32c.h"
#include "util/histogram.h"
#include "util/mutexlock.h"
#include "util/random.h"
#include "util/testutil.h"

int main()
{
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
    assert(status.ok());

    leveldb::Slice key("k1");
    std::string value;
    status = db->Get(leveldb::ReadOptions(), key, &value);
    if (!status.ok())
    {
        std::cout << key.data() << " : " << status.ToString() << std::endl;
    }

    status = db->Put(leveldb::WriteOptions(), key, key);
    if (status.ok())
    {
        std::cout << "Write successfully" << std::endl;
        status = db->Get(leveldb::ReadOptions(), key, &value);
        if (status.ok())
        {
            std::cout << "The value of " << key.data() << " value is " << value << std::endl;
        }
    }

    delete (db);
    return 0;
}
