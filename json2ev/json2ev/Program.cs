using System.Text.Json;
using System.Text.RegularExpressions;
using Newtonsoft.Json.Linq;

namespace json2ev
{
    internal class Program
    {
        static void Main(string[] args)
        {            
            if(args.Length < 2)
            {
                Console.WriteLine("json2ev prefix filename");
                Console.WriteLine("Example: json2ev \"SDIS_\" appsettings.json");
                return;
            }

            string prefix = "export " + args[0];
            string filename = args[1];

            string text = File.ReadAllText(filename);
            JObject json = JObject.Parse(text);

            JToken? token = json.First;

            List<KeyValuePair<string, string>> list = new List<KeyValuePair<string, string>>();
            Walking(token, list);

            list = list.Distinct().ToList();

            foreach (KeyValuePair<string, string> pair in list)
            {
                //Console.WriteLine("{0} {1}", pair.Key, pair.Value);
                
                string result = Regex.Replace(pair.Key, "(?<=\\['.+)\\.(?=.+'\\])", "***");
                result = Regex.Replace(result, "']$", "");
                result = Regex.Replace(result, "]$", "");
                result = Regex.Replace(result, "]\\.", "__");
                result = Regex.Replace(result, "\\['", "__");
                result = Regex.Replace(result, "\\[", "__");
                result = Regex.Replace(result, "\\.", "__");
                result = Regex.Replace(result, "\\*\\*\\*", ".");


                Console.WriteLine("{0}={1}", prefix+result, "\""+pair.Value+"\"");
            }            
        }

        static void Walking(JToken? token, IList<KeyValuePair<string, string>> list)
        {
            if (token == null)
                return;

            //Console.WriteLine(token.Type);

            if (token.Type == JTokenType.String || token.Type == JTokenType.Boolean || token.Type == JTokenType.Integer)
                list.Add(new KeyValuePair<string, string>(token.Path, token.ToString()));
                //Console.WriteLine( "{0} {1}", token.Path, token.ToString() );

            foreach ( var child in token.Children())
            {
                Walking(child, list);
            }

            //Console.WriteLine("---------------");
            Walking(token.Next, list);
        }

        
    }
}