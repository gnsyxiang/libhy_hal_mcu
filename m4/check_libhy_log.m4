dnl ===============================================================
dnl 
dnl Release under GPLv-3.0.
dnl 
dnl @file    check_libhy_log.m4
dnl @brief   
dnl @author  gnsyxiang <gnsyxiang@163.com>
dnl @date    16/08 2023 16:34
dnl @version v0.0.1
dnl 
dnl @since    note
dnl @note     note
dnl 
dnl     change log:
dnl     NO.     Author              Date            Modified
dnl     00      zhenquan.qiu        16/08 2023      create the file
dnl 
dnl     last modified: 16/08 2023 16:34
dnl ===============================================================

# CHECK_LIBHY_LOG()
# --------------------------------------------------------------
# check libhy_log

AC_DEFUN([CHECK_LIBHY_LOG], [

    AC_ARG_ENABLE([hy_log],
        [AS_HELP_STRING([--disable-hy_log], [disable support for hy_log])],
            [], [enable_hy_log=yes])

    case "$enable_hy_log" in
        yes)
            have_hy_log=no

            case "$PKG_CONFIG" in
                '') ;;
                *)
                    HY_LOG_LIBS=`$PKG_CONFIG --libs hy_log 2>/dev/null`

                    case "$HY_LOG_LIBS" in
                        '') ;;
                        *)
                            HY_LOG_LIBS="$HY_LOG_LIBS"
                            have_hy_log=yes
                        ;;
                    esac

                    HY_LOG_INCS=`$PKG_CONFIG --cflags hy_log 2>/dev/null`
                ;;
            esac

            case "$have_hy_log" in
                yes) ;;
                *)
                    save_LIBS="$LIBS"
                    LIBS=""
                    HY_LOG_LIBS=""

                    # clear cache
                    unset ac_cv_search_HyLogInit
                    AC_SEARCH_LIBS([HyLogInit], [hy_log],
                            [have_hy_log=yes
                                HY_LOG_LIBS="$LIBS"],
                            [have_hy_log=no],
                            [])
                    LIBS="$save_LIBS"
                ;;
            esac

            CPPFLAGS_SAVE=$CPPFLAGS
            CPPFLAGS="$CPPFLAGS $HY_LOG_INCS"
            AC_CHECK_HEADERS([hy_log/hy_log.h], [], [have_hy_log=no])

            CPPFLAGS=$CPPFLAGS_SAVE
            AC_SUBST(HY_LOG_INCS)
            AC_SUBST(HY_LOG_LIBS)

            case "$have_hy_log" in
                yes)
                    AC_CHECK_LIB([hy_log], [HyLogInit])
                    AC_DEFINE(HAVE_HY_LOG, 1, [Define if the system has hy_log])
                ;;
                *)
                    AC_MSG_WARN([hy_log is a must but can not be found. You should add the \
directory containing `hy_log.pc' to the `PKG_CONFIG_PATH' environment variable, \
or set `CPPFLAGS' and `LDFLAGS' directly for hy_log, or use `--disable-hy_log' \
to disable support for hy_log encryption])
                ;;
            esac
        ;;
    esac

    # check if we have and should use hy_log
    AM_CONDITIONAL(COMPILE_LIBHY_LOG, [test "$enable_hy_log" != "no" && test "$have_hy_log" = "yes"])
])
