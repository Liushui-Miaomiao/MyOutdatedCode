using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Security.Principal;

namespace Nt_Cheater {
	/// <summary>
	/// 进程操作类
	/// </summary>
	class MyProcess {
		// DLL函数声明

		[DllImportAttribute("kernel32.dll", EntryPoint = "ReadProcessMemory")]
		private static extern bool _ReadProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, IntPtr lpBuffer, int nSize, IntPtr lpNumberOfBytesRead);

		[DllImportAttribute("kernel32.dll", EntryPoint = "WriteProcessMemory")]
		private static extern bool _WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, int[] lpBuffer, int nSize, IntPtr lpNumberOfBytesWritten);

		[DllImportAttribute("kernel32.dll", EntryPoint = "OpenProcess")]
		private static extern IntPtr _OpenProcess(int dwDesiredAccess, bool bInheritHandle, int dwProcessId);

		/// <summary>
		/// 判断指定进程是否存在
		/// </summary>
		/// <param name="name">进程名</param>
		/// <returns>指定进程是否存在</returns>
		public static bool IsExistsProcess(string name) {
			Process[] processes = Process.GetProcessesByName(name);

			return processes.Length > 0;
		}

		/// <summary>
		/// 判断程序是否以管理员身份启动
		/// </summary>
		/// <returns>程序是否以管理员身份启动</returns>
		public static bool IsAdministrator() {
			WindowsIdentity  current = WindowsIdentity.GetCurrent();
			WindowsPrincipal wp      = new WindowsPrincipal(current);

			return wp.IsInRole(WindowsBuiltInRole.Administrator);
		}

		/// <summary>
		/// 通过进程名称获取进程pid
		/// </summary>
		/// <param name="name">进程名</param>
		/// <returns>指定名称进程的pid</returns>
		public static int GetPidByProcessName(string name) {
			int pid = 0;

			if (!IsExistsProcess(name)) {
				goto END;
			}

			Process[] processes = Process.GetProcessesByName(name);
			foreach (Process process in processes) {
				pid = process.Id;

				if (pid > 0) {
					goto END;
				}
			}

		END:
			return pid;
		}

		/// <summary>
		/// 通过进程名称获取进程起始地址
		/// </summary>
		/// <param name="name">进程名</param>
		/// <returns>指定名称进程的起始地址</returns>
		public static IntPtr GetProcessBaseAddr(string name) {
			IntPtr baseAddr = IntPtr.Zero;

			if (!IsExistsProcess(name)) {
				goto END;
			}

			Process[] processes = Process.GetProcessesByName(name);
			foreach (Process process in processes) {
				baseAddr = process.MainModule.BaseAddress;

				if (baseAddr != IntPtr.Zero) {
					goto END;
				}
			}

		END:
			return baseAddr;
		}

		/// <summary>
		/// 打开进程
		/// </summary>
		/// <param name="dwDesiredAccess"></param>
		/// <param name="bInheritHandle"></param>
		/// <param name="dwProcessId"></param>
		/// <returns>进程句柄</returns>
		public static IntPtr OpenProcess(
			int dwDesiredAccess, 
			bool bInheritHandle, 
			int dwProcessId
		) {
			try {
				return _OpenProcess(
					dwDesiredAccess, 
					bInheritHandle, 
					dwProcessId
				);
			}
			catch (Exception) { }

			return IntPtr.Zero;
		}

		/// <summary>
		/// 读进程内存
		/// </summary>
		/// <param name="hProcess"></param>
		/// <param name="lpBaseAddress"></param>
		/// <param name="lpBuffer"></param>
		/// <param name="nSize"></param>
		/// <param name="lpNumberOfBytesRead"></param>
		/// <returns></returns>
		public static bool ReadProcessMemory(
			IntPtr hProcess, IntPtr lpBaseAddress, 
			IntPtr lpBuffer, int nSize, 
			IntPtr lpNumberOfBytesRead
		) {
			try {
				return _ReadProcessMemory(
					hProcess, lpBaseAddress, 
					lpBuffer, nSize, 
					lpNumberOfBytesRead
				);
			}
			catch (Exception) { }

			return false;
		}

		/// <summary>
		/// 写进程内存
		/// </summary>
		/// <param name="hProcess"></param>
		/// <param name="lpBaseAddress"></param>
		/// <param name="lpBuffer"></param>
		/// <param name="nSize"></param>
		/// <param name="lpNumberOfBytesWritten"></param>
		/// <returns></returns>
		public static bool WriteProcessMemory(
			IntPtr hProcess, IntPtr lpBaseAddress, 
			int[]  lpBuffer, int    nSize, 
			IntPtr lpNumberOfBytesWritten
		) {
			try {
				return _WriteProcessMemory(
					hProcess, lpBaseAddress, 
					lpBuffer, nSize, 
					lpNumberOfBytesWritten
				);
			}
			catch (Exception) { }

			return false;
		}
	}
}
