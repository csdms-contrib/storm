#! /usr/bin/env python
#
# Tests for the Fortran version of `storm`.
#
# Call with:
#   $ nosetests -sv
#
# Mark Piper (mark.piper@colorado.edu)

from nose.tools import *
import os
import shutil
from subprocess import call

# Globals
data_dir = os.path.join(os.getcwd(), 'testing', 'data')
f_dir = os.path.join(os.getcwd(), 'f')
input_file = 'wind.in'
output_files = ('WDIR.DATA', 'WINDX.DATA', 'WINDY.DATA')
output_file_lengths = (100, 104, 104)

# Fixtures -------------------------------------------------------------

def setup_module():
    '''
    Called before any tests are performed.
    '''
    print('Fortran tests:')
    os.chdir(f_dir)

def teardown_module():
    '''
    Called after all tests have completed.
    '''
    call(['make', 'clean'])
    for fn in output_files: os.remove(fn)

def setup():
    '''
    Called at start of any test using it @with_setup()
    '''
    shutil.copy(os.path.join(data_dir, input_file), f_dir)

def teardown():
    '''
    Called at end of any test using it @with_setup()
    '''
    os.remove(input_file)

# Tests ----------------------------------------------------------------

def test_compile():
    '''
    Test whether `storm` compiles
    '''
    call(['make'])

def test_no_input_file():
    '''
    Check that storm fails without input file
    '''
    r = call(['./storm'])
    assert_not_equal(r, 0)

@with_setup(setup, teardown)
def test_output_files_exist():
    '''
    Test for creation of the three named output files
    '''
    r = call(['./storm'])
    for fname in output_files:
        assert_true(os.path.exists(fname))

@with_setup(setup, teardown)
def test_output_file_lengths():
    '''
    Test the lengths of the three named output files
    '''
    r = call(['./storm'])
    for i in range(len(output_files)):
        n_lines = sum(1 for line in open(output_files[i]))
        assert_equal(n_lines, output_file_lengths[i])
