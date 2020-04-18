using Microsoft.Samples.DPAPI;
using System;
using System.Text;

class TestStub 
{
	public static void Main(string[] args) 
	{
		string data = "Look out for the Balrog in Moria.";
		string name="MySecret";
		Console.WriteLine("String is: " + data);
		string s = DataProtection.ProtectData(data, 
			name, 
			NativeMethods.UIForbidden);
		if (null == s) 
		{
			Console.WriteLine("Failure to encrypt");
			return;
		}
		Console.WriteLine("Encrypted Data: " + s);
		s = DataProtection.UnprotectData(s);
		Console.WriteLine("Cleartext: " + s);
	}
}
