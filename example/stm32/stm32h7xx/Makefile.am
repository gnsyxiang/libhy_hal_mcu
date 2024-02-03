# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    02/02 2024 11:19
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        02/02 2024      create the file
# 
#     last modified: 02/02 2024 11:19
# ===============================================================

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
bin_PROGRAMS    =
_elf_file       =

# ---------------------
# add necessary content
# ---------------------
_no_error_com   +=

_define_com     +=

_include_com    += \
                   -I$(top_srcdir)/include/$(vender)/$(chip) \
                   -I$(top_srcdir)/include

_sources_com    +=

_cppflags_com   += \
                   $(_no_error_com) \
                   $(_include_com) \
                   $(_define_com)

_cflags_com     +=

_cxxflags_com   +=

_ldflags_com    +=

_ldadd_com      += \
                   $(top_builddir)/src/lib$(project_name).la \
                   $(ldadd_com)

_ldflags_com    += -T$(top_srcdir)/src/stm32/stm32h7xx/STM32H743ZITx_FLASH.ld

_elf_file                   += hy_led_demo
bin_PROGRAMS                += hy_led_demo.elf
hy_led_demo_elf_SOURCES     = $(_sources_com) hy_led_demo.c
hy_led_demo_elf_CPPFLAGS    = $(_cppflags_com)
hy_led_demo_elf_CFLAGS      = $(_cflags_com)
hy_led_demo_elf_CXXFLAGS    = $(_cxxflags_com)
hy_led_demo_elf_LDFLAGS     = $(_ldflags_com) -Wl,--gc-sections,-Map=hy_led_demo.map,-cref,-u,Reset_Handler
hy_led_demo_elf_LDADD       = $(_ldadd_com)

install-exec-hook:
	for file in $(_elf_file); do \
		@gcc_prefix@objcopy -O binary $$file.elf $$file.bin; \
		@gcc_prefix@size $$file.elf; \
	done
	$(INSTALL_PROGRAM_ENV) $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL_PROGRAM) *.bin "$(DESTDIR)$(bindir)$$dir"
