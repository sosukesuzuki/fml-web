import { ChangeEvent, useMemo, useState } from "react";
import { Input, Text } from "@kuma-ui/core";

type Fml = {
  parse: (expression: string) => string;
  compile: (expression: string) => string;
  test: (expression: string, text: string) => 1 | 0;
};

let fml: Fml | null = null;

async function loadFml(): Promise<Fml> {
  // @ts-ignore
  const { default: module } = await import("lib-fml-web");
  const Module = await module();
  const fml = {
    parse: Module.cwrap("parse", "string", ["string"], []),
    compile: Module.cwrap("compileToInstructions", "string", ["string"], []),
    test: Module.cwrap("test", "number", ["string", "string"], []),
  };
  return fml;
}

export default function FmlTable() {
  const [expression, setExpression] = useState("");
  const [text, setText] = useState("");
  const result = useMemo(() => {
    if (fml === null || expression === "" || text === "") {
      return "";
    }
    return fml.test(expression, text) === 1 ? "TRUE" : "FALSE";
  }, [expression, text]);
  const ast = useMemo(() => {
    if (fml === null || expression === "") {
      return "";
    }
    return fml.parse(expression);
  }, [expression]);
  const instructions = useMemo(() => {
    if (fml === null || expression === "") {
      return "";
    }
    return fml.compile(expression);
  }, [expression]);
  if (fml === null) {
    throw loadFml().then((fmlApi) => {
      fml = fmlApi;
    });
  }
  return (
    <table>
      <tbody>
        <tr>
          <td>
            <Text>Expression:</Text>
          </td>
          <td>
            <Input
              value={expression}
              onChange={(e: ChangeEvent<HTMLInputElement>) => {
                setExpression(e.target.value);
              }}
            />
          </td>
        </tr>
        <tr>
          <td>
            <Text>Text:</Text>
          </td>
          <td>
            <Input
              value={text}
              onChange={(e: ChangeEvent<HTMLInputElement>) => {
                setText(e.target.value);
              }}
            />
          </td>
        </tr>
        <tr>
          <td>
            <Text>Result:</Text>
          </td>
          <td>{result}</td>
        </tr>
        <tr>
          <td>
            <Text>AST:</Text>
          </td>
          <td>{ast}</td>
        </tr>
        <tr>
          <td>
            <Text>Instructions:</Text>
          </td>
          <td>{instructions}</td>
        </tr>
      </tbody>
    </table>
  );
}
