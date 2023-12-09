import { ChangeEvent, useMemo, useState } from "react";
import { Input, Text, Box } from "@kuma-ui/core";

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

function CodeBlock({ children }: { children: string }) {
  return (
    <Box border="1px solid black" width="100%" p={4}>
      <pre style={{ margin: 0 }}>
        <code style={{ fontFamily: "Monaco, monospace" }}>{children}</code>
      </pre>
    </Box>
  );
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
    return JSON.stringify(JSON.parse(fml.parse(expression)), null, 2);
  }, [expression]);

  const instructions = useMemo(() => {
    if (fml === null || expression === "") {
      return "";
    }
    const insts: string[] = JSON.parse(fml.compile(expression));
    let longestInstLength = 0;
    let longestIdxLength = 0;
    const parsed: { idx: number; instruction: string; operands: string[] }[] =
      insts.map((instStr, idx) => {
        longestInstLength = Math.max(longestInstLength, instStr.length);
        longestIdxLength = Math.max(longestIdxLength, idx.toString().length);
        const [instruction, ...operands] = instStr.split(" ");
        return { idx, instruction, operands };
      });
    return parsed.reduce((acc, { idx, instruction, operands }) => {
      const operandsStr = operands.join(", ");
      const idxPadding = " ".repeat(longestIdxLength - idx.toString().length);
      const instPadding = " ".repeat(longestInstLength - instruction.length);
      return (
        acc +
        `${idx}${idxPadding}: ${instruction}${instPadding} ${operandsStr}\n`
      );
    }, "");
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
            <Text m={0}>Expression:</Text>
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
            <Text m={0}>Text:</Text>
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
            <Text m={0}>Result:</Text>
          </td>
          <td>{result}</td>
        </tr>
        <tr>
          <td>
            <Text m={0}>AST:</Text>
          </td>
          <td>
            <CodeBlock>{ast}</CodeBlock>
          </td>
        </tr>
        <tr>
          <td>
            <Text m={0}>Instructions:</Text>
          </td>
          <td>
            <CodeBlock>{instructions}</CodeBlock>
          </td>
        </tr>
      </tbody>
    </table>
  );
}
