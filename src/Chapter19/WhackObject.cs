using System;
using System.Text;
using System.IO;

namespace WhackObject {
    class Class1 {
        static Random _rand;
        static int getNum() {
            return _rand.Next(-1000,1000);
        }
        
        static string getString() {
            StringBuilder s = new StringBuilder();
            for (int i = 0; i < _rand.Next(1,16000); i++)
                s.Append("A");
            return s.ToString();
        }
        
        static void Main(string[] args) {
            _rand = new Random(unchecked((int)DateTime.Now.Ticks)); 
            string CRLF = "\r\n";

            try  {
                string htmlFile = "test.html";
                string prolog = 
@"<HTML><BODY><OBJECT ID='DISysMon' WIDTH='100%' HEIGHT='100%'" +
                 "CLASSID='CLSID:C4D2D8E0-D1DD-11CE-940F-008029004347'>";
                string epilog = @"</OBJECT></BODY></HTML>";

                StreamWriter sw = new StreamWriter(htmlFile);
                sw.Write(prolog + CRLF);

                string [] numericArgs = {
                    "ForeColor","SampleCount",
                    "TimeBarColor","ReadOnly"};

                string [] stringArgs = {
                    "LogFileName","YAxisLabel","XAxisLabel"};

                for (int i=0; i < numericArgs.Length; i++) 
                    sw.Write(@"<PARAM NAME={0} VALUE={1}>{2}",
numericArgs[i],getNum(),CRLF);

                for (int j=0; j < stringArgs.Length; j++) 
                    sw.Write(@"<PARAM NAME={0} VALUE={1}>{2}",
stringArgs[j],getString(),CRLF);

                sw.Write(epilog + CRLF);

                sw.Flush();
                sw.Close();
            } catch (IOException e){
                Console.Write(e.ToString());
            }
        }
     }
}
