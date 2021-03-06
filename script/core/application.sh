#!/bin/bash

function cavan-read-choise()
{
	local def_choise choise message

	if [ "$2" = "" ] || [ "$2" = "y" ] || [ "$2" = "Y" ]
	then
		def_choise="Y"
		message="$1 [Y/n]? "
	else
		def_choise="N"
		message="$1 [y/N]? "
	fi

	while :
	do
		echo -n "${message}"
		read choise
		[ "${choise}" ] || choise=${def_choise}
		case ${choise} in
			Y | y)
				return 0 ;;
			n | N)
				return 1 ;;
			*)
				echo "Please input y/Y/n/N/Enter" ;;
		esac
	done
}

function cavan-cross-config()
{
	local command

	command="./configure --prefix=/usr --build=$(gcc -dumpmachine) --target=arm-cavan-linux-gnueabi $*"
	cavan-read-choise "Command = \"${command}\"" "Y" || return 1
	command || return 1

	return 0
}

function cavan-app-install()
{
	local command

	if [ "$1" ]
	then
		command="make DESTDIR=$1 install"
	else
		command="make install"
	fi

	cavan-read-choise "Command = \"${command}\"" "Y" || return 1
	command || return 1

	return 0
}

function cavan-git-daemon-run()
{
	local PORT BASE_PATH COMMAND

	PORT=${1-"7777"}
	BASE_PATH=${2-${HOME}/git}

	mkdir ${BASE_PATH} -p || exit 1

	echo "BASE_PATH = ${BASE_PATH}"
	echo "PORT = ${PORT}"

	COMMAND="$(git --exec-path)/git-daemon --verbose --port=${PORT} --export-all --enable=receive-pack --enable=upload-pack --enable=upload-archive --base-path=${BASE_PATH}"

	if which cavan-service > /dev/null
	then
		cavan-service --start -s 0 --exec "${COMMAND}"
	else
		${COMMAND}
	fi
}

function cavan-daemon-run()
{
	cavan-tcp_dd_server -ds0
	cavan-tcp_dd_server -ds0 --udp

	while cavan-alarm remove 0 -l 2>&1 > /dev/null
	do
		echo "Remove a alarm succesfually"
	done

	cavan-alarm add cavan-sprd-compile ${CAVAN_HOME}/script/configs/project.cfg -lt 23:00 -r 1d
	cavan-alarm list -l

	cavan-tcp_proxy -adp 9999
	cavan-tcp_proxy --daemon --host mirrors.ustc.edu.cn --pport 80 --port 6666
	squid
	distccd --allow "0.0.0.0/0" --port 3333 --daemon
	cavan-web_proxy -dp 9090 --host mirrors.ustc.edu.cn
	cavan-git-daemon-run

	return 0
}

function cavan-apk-rename()
{
	local fn nfn

	for fn in *-[0-9].apk
	do
		nfn="${fn%-*.apk}.apk"
		mv -v "${fn}" "${nfn}"
	done
}

function cavan-android-buildenv()
{
	export TARGET_GCC_VERSION_EXP="${1-4.7.4}-$(uname -m)"

	echo "TARGET_GCC_VERSION_EXP = ${TARGET_GCC_VERSION_EXP}"

	TOOLCHIAN_GNUEABI="${CAVAN_TOOLCHIAN_GNUEABI}-${TARGET_GCC_VERSION_EXP}"
	TOOLCHIAN_ANDROIDEABI="${CAVAN_TOOLCHIAN_ANDROIDEABI}-${TARGET_GCC_VERSION_EXP}"

	echo "TOOLCHIAN_GNUEABI = ${TOOLCHIAN_GNUEABI}"
	echo "TOOLCHIAN_ANDROIDEABI = ${TOOLCHIAN_ANDROIDEABI}"

	[ -d "${TOOLCHIAN_GNUEABI}" ] && [ -d "${TOOLCHIAN_ANDROIDEABI}" ] ||
	{
		echo "${TOOLCHIAN_GNUEABI} or ${TOOLCHIAN_ANDROIDEABI} not found"
		return 1
	}

	DIR_ANDROID_PREBUILT_ARM_GCC="prebuilts/gcc/linux-x86/arm"

	(
		cd "${DIR_ANDROID_PREBUILT_ARM_GCC}" &&
		{
			rm -f "arm-eabi-${TARGET_GCC_VERSION_EXP}" && ln -vsf "${TOOLCHIAN_GNUEABI}" "arm-eabi-${TARGET_GCC_VERSION_EXP}" || return 1
			rm -f "arm-linux-androideabi-${TARGET_GCC_VERSION_EXP}" ] && ln -vsf "${TOOLCHIAN_ANDROIDEABI}" "arm-linux-androideabi-${TARGET_GCC_VERSION_EXP}" || return 1
		}
	)

	DIR_INCLUDE_SYS="$(find /usr/include/ -maxdepth 2 -type d -name sys)"
	FILE_CAPABILITY_H="${DIR_INCLUDE_SYS}/capability.h"

	echo "DIR_INCLUDE_SYS = ${DIR_INCLUDE_SYS}"
	echo "FILE_CAPABILITY_H = ${FILE_CAPABILITY_H}"

	[ -f "${FILE_CAPABILITY_H}" ] || su -c "echo \"#include <sys/resource.h>\" > \"${FILE_CAPABILITY_H}\""

	export HOST_TOOLCHAIN_PREFIX="prebuilts/gcc/linux-x86/host/i686-linux-glibc2.7-4.6"

	echo "HOST_TOOLCHAIN_PREFIX = ${HOST_TOOLCHAIN_PREFIX}"
}

function cavan-set-jdk-version()
{
	[ "$1" ] || return 1

	if [[ $1 = jdk* ]]
	then
		JDK_VERSION="$1"
	else
		JDK_VERSION="jdk$1"
	fi

	[ -d "/tools/${JDK_VERSION}" ] || for fn in /tools/${JDK_VERSION}*
	do
		[ -d "${fn}" ] && JDK_VERSION="$(basename ${fn})"
	done

	[ -d "/tools/${JDK_VERSION}" ] || return 1

	echo "JDK_VERSION = ${JDK_VERSION}"

	[ "${PATH_BAK}" ] && PATH="${PATH_BAK}"

	source ${CAVAN_HOME}/script/core/bashrc.sh
}

function cavan-chdir-by-file()
{
	local target_file

	target_file=$1
	[ "${target_file}" ] || return 1

	while :;
	do
		[ -f "${target_file}" ] &&
		{
			return 0
		}

		cd .. || break
		[ "${PWD}" = "/" ] && break
	done

	return 1
}

function cavan-get-root-by-file()
{
	(cavan-chdir-by-file $1 && pwd)
}

function cavan-mm-push()
{
	local kernel_root file_list

	kernel_root=$(cavan-get-root-by-file "include/linux/kernel.h")

	if [ "${kernel_root}" ]
	then
		echo "kernel_root = ${kernel_root}"
		(
			cd "${kernel_root}" || return 1
			[ -e ".config" ] || make ${1-jw100}_defconfig || return 1
			make ${1-jw100.img} -j8 && cavan-tcp_dd -wa --auto kernel.img resource.img || return 1
		) || return 1
	else
		file_list=$(mm -j8 | cavan-tee | grep "^Install:" | sed 's/^Install:\s*//g'; [ "${PIPESTATUS[0]}" = "0" ]) || return 1
		cavan-android-push ${file_list} || return 1
	fi

	return 0
}

function cavan-mm-push-reboot()
{
	cavan-mm-push && adb reboot && return 0

	return 1
}

function cavan-android-auto-push()
{
	local system_path src_path dest_path

	if [ "$1" ]
	then
		system_path=$1
	elif [ "${ANDROID_PRODUCT_OUT}" ]
	then
		system_path="${ANDROID_PRODUCT_OUT}/system"
	else
		system_path="."
	fi

	echo "system_path = ${system_path}"

	adb start-server || return 1

	(
		cd "${system_path}" || return 1

		[ -f "build.prop" -a -f "lib/libandroid_runtime.so" ] ||
		{
			echo "This path is not system"
			return 1
		}

		cavan-inotify . | while read line
		do
			adb wait-for-device && adb root || continue
			adb wait-for-device && adb remount || continue

			src_path="${line:2}"
			dest_path="/system/${src_path}"

			echo "push: ${src_path} => ${dest_path}"
			adb push "${src_path}" "${dest_path}"
		done
	)
}
