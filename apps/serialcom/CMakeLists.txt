#
# Copyright 2019, DornerWorks
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#
# @TAG(DORNERWORKS_BSD)
#

cmake_minimum_required(VERSION 3.7.2)
project(serialcom C)

set(CAmkESCPP ON CACHE BOOL "" FORCE)
includeGlobalComponents()
DeclareCAmkESComponent(
    SerialApplication
    SOURCES
    components/SerialApplication/src/application.c
    LIBS
    sel4allocman
    sel4simple
    sel4simple-default
    sel4utils
    sel4vka
    sel4vspace
    sel4platsupport
    )
DeclareCAmkESRootserver(serialcom.camkes)
