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

noinst_LTLIBRARIES = lib@vender@_@chip@.la

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
                   -I$(top_srcdir)/include/$(vender)/$(chip) \
                   -I$(top_srcdir)/include/$(vender) \
                   -I$(top_srcdir)/include \
                   \
                   -I$(includedir)/hy_mcu


_sources_com    += \
                   hy_hal_gpio.c \
                   hy_hal_isr.c \
                   hy_hal_sys.c \
                   hy_hal_time.c \
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

lib@vender@_@chip@_la_SOURCES   = $(_sources_com)
lib@vender@_@chip@_la_CPPFLAGS  = $(_cppflags_com)
lib@vender@_@chip@_la_CCASFLAGS = $(_cppflags_com)
lib@vender@_@chip@_la_CFLAGS    = $(_cflags_com)
lib@vender@_@chip@_la_CXXFLAGS  = $(_cxxflags_com)
lib@vender@_@chip@_la_LDFLAGS   = $(_ldflags_com)
lib@vender@_@chip@_la_LIBADD    = $(_ldadd_com)
