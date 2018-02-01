def new(num_buckets=256):
        aMap = []
        for i in range(0, num_buckets):
                aMap.append([])
        return aMap

def hash_key(aMap, key):
        print "greg: aMap = ", aMap
        print "greg: key = ", key
        print "greg: hash(key) = ", hash(key)
        print "greg: len(aMap) = ", len(aMap)
        print "greg: hash(key) % len(aMap) = ", hash(key) % len(aMap)
        return hash(key) % len(aMap)

def get_bucket(aMap, key):
        bucket_id = hash_key(aMap, key)
        return aMap[bucket_id]

def get_slot(aMap, key, default=None):
        bucket = get_bucket(aMap, key
        for i, kv, in enumerate(bucket):
                k, v = kv
