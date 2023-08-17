# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    16/08 2023 15:42
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        16/08 2023      create the file
# 
#     last modified: 16/08 2023 15:42
# ===============================================================

SUBDIRS =

if COMPILE_SELECT_CHIP_STM32H7XX
SUBDIRS += stm32h7xx
endif

noinst_LTLIBRARIES = libstm32.la

# ------------------
# defining variables
# ------------------
_no_error_com   =
_define_com     =
_include_com    = $(include_com)
_sources_com    =
_cppflags_com   =
_cflags_com     =
_cxxflags_com   =
_ldflags_com    =
_ldadd_com      =

# ---------------------
# add necessary content
# ---------------------
_no_error_com   +=

_define_com     +=

_include_com    += -I$(top_srcdir)/include

_sources_com    +=

_cppflags_com   += \
                   $(_no_error_com) \
                   $(_include_com)  \
                   $(_define_com)

_cflags_com     +=

_cxxflags_com   +=

if COMPILE_SELECT_CHIP_STM32H7XX
_ldadd_com      += $(top_builddir)/src/stm32/stm32h7xx/libstm32h7xx.la
endif

_ldadd_com      += $(ldadd_com)

libstm32_la_SOURCES    = $(_sources_com)
libstm32_la_CPPFLAGS   = $(_cppflags_com)
libstm32_la_CFLAGS     = $(_cflags_com)
libstm32_la_CXXFLAGS   = $(_cxxflags_com)
libstm32_la_LDFLAGS    = $(_ldflags_com)
libstm32_la_LIBADD     = $(_ldadd_com)
