import { useEffect } from "react";

export default function App() {
  useEffect(() => {
    (async () => {
      // @ts-ignore
      const { default: module } = await import("lib-fml-web");
      const Module = await module();
      const api = {
        parse: Module.cwrap("parse", "string", ["string"], []),
        compile: Module.cwrap(
          "compileToInstructions",
          "string",
          ["string"],
          []
        ),
        test: Module.cwrap("test", "number", ["string", "string"], []),
      };
      const parseResult = api.parse("a|a");
      const compileResult = api.compile("a|a");
      const testResult = api.test("a|b", "c");
      console.log(parseResult);
      console.log(compileResult);
      console.log(testResult);
    })();
  }, []);

  return <h1>Hello</h1>;
}
