namespace Microsoft.Samples.DPAPI {

	using System;
	using System.Runtime.InteropServices;
	using System.Text;
	using System.Security;

	[SuppressUnmanagedCodeSecurityAttribute]
	public class NativeMethods {

		static public IntPtr NullPtr = ((IntPtr)((int)(0)));

		// platform invoke declarations
		[DllImport("crypt32", CharSet=System.Runtime.InteropServices.CharSet.Unicode, SetLastError=true, ExactSpelling=true)]
		public static extern bool CryptProtectData(ref DATA_BLOB dataIn, string szDataDescr, IntPtr optionalEntropy, 
			IntPtr pvReserved, ref CRYPTPROTECT_PROMPTSTRUCT pPromptStruct,
			int dwFlags, ref DATA_BLOB pDataOut);


		[DllImport("crypt32", CharSet=System.Runtime.InteropServices.CharSet.Unicode, SetLastError=true, ExactSpelling=true)]
		public static extern bool CryptUnprotectData(ref DATA_BLOB dataIn, StringBuilder ppszDataDescr,
			IntPtr optionalEntropy, IntPtr pvReserved,
			ref CRYPTPROTECT_PROMPTSTRUCT pPromptStruct, int dwFlags,
			ref DATA_BLOB pDataOut);


		[DllImport("kernel32")]
		public static extern IntPtr LocalFree(IntPtr hMem);
        
		[StructLayout(LayoutKind.Sequential, CharSet=CharSet.Unicode)]
			public struct DATA_BLOB {
			public int cbData;
			public IntPtr pbData;
		}

		public const int PromptOnProtect = 0x2;
		public const int PromptOnUnprotect = 0x1;
		public const int UIForbidden = 0x1;
		public const int PromptStrong = 0x08;
		public const int LocalMachine = 0x4;
		public const int CredSync = 0x8;
		public const int Audit = 0x10;
		public const int NoRecovery = 0x20;
		public const int VerifyProtection = 0x40;

		[StructLayout(LayoutKind.Sequential, CharSet=CharSet.Unicode)]
			public struct CRYPTPROTECT_PROMPTSTRUCT {
			public int cbSize;  //= Marshal.SizeOf(typeof(CRYPTPROTECT_PROMPTSTRUCT));
			public int dwPromptFlags;  //= 0;
			public IntPtr hwndApp;  //= IntPtr.Zero;
			public string szPrompt;  //= null;
		}
	}
}
