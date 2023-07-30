project('datastructures', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++20'])

incdir = include_directories('inc')

gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_dep')

srcs = [
  'main.cpp',
  'test/vector.cpp',
  'test/linkedlist.cpp',
  'test/hashmap.cpp',
  'test/btreemap.cpp',
]

executable('datastructures',
           srcs,
           dependencies : [gtest_dep],
           install : true,
           override_options : ['cpp_std=c++20'],
           include_directories : incdir)
