#!/usr/bin/python
import json, random

d= {
    'foo': 'This is a test string!',
    'bar': 123.456,
    'argle': True
}

result= {}
for i in xrange(1024*1024):
    r= random.randrange(1024*1024*1024)
    result['key'+str(r)]= d

json.dump(result, open('test.json', 'wt'), sort_keys=True, indent=4)
