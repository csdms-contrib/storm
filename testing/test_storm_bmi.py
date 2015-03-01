#! /usr/bin/env python
#
# Tests for the BMI version of `storm`.
#
# Call with:
#   $ nosetests -sv
#
# Mark Piper (mark.piper@colorado.edu)

from nose.tools import *
import os
import shutil
from subprocess import call

# Global variables
start_dir = os.getcwd()
data_dir = os.path.join(start_dir, 'testing', 'data')
input_file1 = os.path.join(data_dir, 'test1.in')
input_file2 = os.path.join(data_dir, 'test2.in')
build_dir = os.path.join(start_dir, 'build')
exe = './bmi/storm'

# Fixtures -------------------------------------------------------------

def setup_module():
    '''
    Called before any tests are performed.
    '''
    print('*** BMI tests')
    os.mkdir(build_dir)
    os.chdir(build_dir)

def teardown_module():
    '''
    Called after all tests have completed.
    '''
    os.chdir(start_dir)
    shutil.rmtree(build_dir)

# Tests ----------------------------------------------------------------

def test_configure():
    '''
    Test whether CMake executes successfully
    '''
    call(['cmake', '..'])

def test_compile():
    '''
    Test whether `storm` compiles
    '''
    call(['make'])

def test_without_input_file():
    '''
    Check that storm runs without an input file
    '''
    r = call([exe])
    assert_equal(r, 0)

def test_with_singlestep_input_file():
    '''
    Check that storm runs with a one-step input file
    '''
    r = call([exe, input_file1])
    assert_equal(r, 0)

def test_with_multistep_input_file():
    '''
    Check that storm runs with a multi-step input file
    '''
    r = call([exe, input_file2])
    assert_equal(r, 0)
