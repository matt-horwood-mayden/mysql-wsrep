#ifndef ATOMIC_GCC_BUILTINS_INCLUDED
#define ATOMIC_GCC_BUILTINS_INCLUDED

/* Copyright (c) 2008, 2010, Oracle and/or its affiliates. All rights reserved.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License, version 2.0,
   as published by the Free Software Foundation.

   This program is also distributed with certain software (including
   but not limited to OpenSSL) that is licensed under separate terms,
   as designated in a particular file or component or in included license
   documentation.  The authors of MySQL hereby grant you an additional
   permission to link the program and your derivative works with the
   separately licensed software that they have included with MySQL.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License, version 2.0, for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA */

#define make_atomic_add_body(S)                     \
  v= __sync_fetch_and_add(a, v);
#define make_atomic_fas_body(S)                     \
  v= __sync_lock_test_and_set(a, v);
#define make_atomic_cas_body(S)                     \
  int ## S sav;                                     \
  int ## S cmp_val= *cmp;                           \
  sav= __sync_val_compare_and_swap(a, cmp_val, set);\
  if (!(ret= (sav == cmp_val))) *cmp= sav

#ifdef MY_ATOMIC_MODE_DUMMY
#define make_atomic_load_body(S)   ret= *a
#define make_atomic_store_body(S)  *a= v
#define MY_ATOMIC_MODE "gcc-builtins-up"

#else
#define MY_ATOMIC_MODE "gcc-builtins-smp"
#define make_atomic_load_body(S)                    \
  ret= __sync_fetch_and_or(a, 0);
#define make_atomic_store_body(S)                   \
  (void) __sync_lock_test_and_set(a, v);
#endif

#endif /* ATOMIC_GCC_BUILTINS_INCLUDED */
