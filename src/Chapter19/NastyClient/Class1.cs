using System;
using System.Net;
using System.Text;

namespace NastyWebClient {
	class NastyWebClientClass {

		static void Main(string[] args) {
			if (args.Length < 1) return;
			string uri = args[0];

			WebClient client = new WebClient();
  
			client.Credentials = CredentialCache.DefaultCredentials;
			client.Headers.Add(@"IWonderIfThisWillCrash:" + new String('a',32000));
			client.Headers.Add(@"User-agent: HackZilla/v42.42 WindowsXP");
		
			try {
				// make request, and get response data
				byte[] data = client.DownloadData(uri);
				WebHeaderCollection header = client.ResponseHeaders;
				bool isText = false;
				for (int i=0; i < header.Count; i++) {
					string headerHttp = header.GetKey(i);
					string headerHttpData = header.Get(i);
					Console.WriteLine(headerHttp + ":" + headerHttpData);
					if (headerHttp.ToLower().StartsWith("content-type") && 
						headerHttpData.ToLower().StartsWith("text")) 
						isText = true;
				}

				if (isText) {	
					string download = Encoding.ASCII.GetString(data);
					Console.WriteLine(download);
				}
		
			} 
			catch (WebException e) {
				Console.WriteLine(e.ToString());
			}
		}
	}
}
