// DataProtection.cs
namespace Microsoft.Samples.DPAPI {

    using System;
    using System.Runtime.InteropServices;
    using System.Text;

    public class DataProtection {
        // Protect string and return base64 encoded data.
        public static string ProtectData(string data, 
  string name, 
  int flags) {
            byte[] dataIn = Encoding.Unicode.GetBytes(data);
            byte[] dataOut = ProtectData(dataIn, name, flags);

            return (null != dataOut)
                ? Convert.ToBase64String(dataOut)
                : null;
        }

        // Unprotect base64-encoded data and return string
        public static string UnprotectData(string data) {
            byte[] dataIn = Convert.FromBase64String(data);
            byte[] dataOut = UnprotectData(dataIn,
NativeMethods.UIForbidden | NativeMethods.VerifyProtection);

            return (null != dataOut) 
                ? Encoding.Unicode.GetString(dataOut)
                : null;
        }

        ////////////////////////
        // Internal functions //
        ////////////////////////

        internal static byte[] ProtectData(byte[] data, 
          string name, 
          int dwFlags) {
            byte[] cipherText = null;

            // Copy data into unmanaged memory.
            NativeMethods.DATA_BLOB din = 
                new NativeMethods.DATA_BLOB();
            din.cbData = data.Length;
            din.pbData = Marshal.AllocHGlobal(din.cbData);
            Marshal.Copy(data, 0, din.pbData, din.cbData);

            NativeMethods.DATA_BLOB dout = 
                new NativeMethods.DATA_BLOB();

            NativeMethods.CRYPTPROTECT_PROMPTSTRUCT ps = 
                new NativeMethods.CRYPTPROTECT_PROMPTSTRUCT();
         
            InitPromptstruct(ref ps);

            try {
                bool ret = 
                    NativeMethods.CryptProtectData(
                        ref din, 
                        name, 
                        NativeMethods.NullPtr,                                                           
                        NativeMethods.NullPtr, 
                        ref ps, 
                        dwFlags, ref dout);

                if (ret) {
                    cipherText = new byte[dout.cbData];
                    Marshal.Copy(dout.pbData, 
                                 cipherText, 0, dout.cbData);
                    NativeMethods.LocalFree(dout.pbData);
                } else {
                    #if (DEBUG)
                    Console.WriteLine("Encryption failed: " + 
                        Marshal.GetLastWin32Error().ToString());
                    #endif
                }
            }
            finally {
                if ( din.pbData != IntPtr.Zero )
                    Marshal.FreeHGlobal(din.pbData);
            }

            return cipherText;
        }

        internal static byte[] UnprotectData(byte[] data, 
                                             int dwFlags) {
            byte[] clearText = null;

            // Copy data into unmanaged memory.
            NativeMethods.DATA_BLOB din = 
                new NativeMethods.DATA_BLOB();
            din.cbData = data.Length;
            din.pbData = Marshal.AllocHGlobal(din.cbData);
            Marshal.Copy(data, 0, din.pbData, din.cbData);

            NativeMethods.CRYPTPROTECT_PROMPTSTRUCT ps = 
                new NativeMethods.CRYPTPROTECT_PROMPTSTRUCT();
         
            InitPromptstruct(ref ps);

            NativeMethods.DATA_BLOB dout = 
                new NativeMethods.DATA_BLOB();

            try {
                bool ret = 
                    NativeMethods.CryptUnprotectData(
                        ref din, 
                        null, 
                        NativeMethods.NullPtr,
                        NativeMethods.NullPtr, 
                        ref ps, 
                        dwFlags, 
                        ref dout);

                if (ret) {
                    clearText = new byte[ dout.cbData ];
                    Marshal.Copy(dout.pbData, 
                                 clearText, 0, dout.cbData);
                    NativeMethods.LocalFree(dout.pbData);
                } else {
                    #if (DEBUG)
                    Console.WriteLine("Decryption failed: " + 
                        Marshal.GetLastWin32Error().ToString());
                    #endif
                }
            }

            finally {
                if ( din.pbData != IntPtr.Zero )
                    Marshal.FreeHGlobal(din.pbData);
            }

            return clearText;
        }

        static internal void InitPromptstruct(
            ref NativeMethods.CRYPTPROTECT_PROMPTSTRUCT ps) {
            ps.cbSize = Marshal.SizeOf(
                typeof(NativeMethods.CRYPTPROTECT_PROMPTSTRUCT));
            ps.dwPromptFlags = 0;
            ps.hwndApp = NativeMethods.NullPtr;
            ps.szPrompt = null;
        }
    }
}
