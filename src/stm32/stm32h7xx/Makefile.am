# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    16/08 2023 15:45
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        16/08 2023      create the file
# 
#     last modified: 16/08 2023 15:45
# ===============================================================

noinst_LTLIBRARIES = libstm32h7xx.la

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

_include_com    += \
                   -I$(top_srcdir)/include/stm32 \
                   -I$(top_srcdir)/include

_sources_com    += \
                   hy_hal_uart.c \
                   system_stm32h7xx.c \
                   startup_stm32h743xx.s

_cppflags_com   += \
                   $(_no_error_com) \
                   $(_include_com)  \
                   $(_define_com)

_cflags_com     +=

_cxxflags_com   +=

_ldadd_com      += $(ldadd_com)

if COMPILE_LIBHY_MCU
_include_com    += $(HY_MCU_INCS)
_ldadd_com      += $(HY_MCU_LIBS)
endif

libstm32h7xx_la_SOURCES     = $(_sources_com)
libstm32h7xx_la_CPPFLAGS    = $(_cppflags_com)
libstm32h7xx_la_CCASFLAGS   = $(_cppflags_com)
libstm32h7xx_la_CFLAGS      = $(_cflags_com)
libstm32h7xx_la_CXXFLAGS    = $(_cxxflags_com)
libstm32h7xx_la_LDFLAGS     = $(_ldflags_com)
libstm32h7xx_la_LIBADD      = $(_ldadd_com)
