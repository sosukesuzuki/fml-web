import { useEffect } from "react";

export default function App() {
  useEffect(() => {
    (async () => {
      // @ts-ignore
      const { default: module } = await import("lib-fml-web");
      const Module = await module();
      const api = {
        parse: Module.cwrap("parse", "string", ["string"], []),
      };
      const result = api.parse("a|a");
      console.log(result);
    })();
  }, []);

  return <h1>Hello</h1>;
}
