import { Box, Heading, Link, Text } from "@kuma-ui/core";
import { Suspense } from "react";
import FmlTable from "./FmlTable";

export default function App() {
  return (
    <Box fontFamily="Monaco, monospace">
      <Box p={16} bg="black">
        <Box width={680} margin="0 auto">
          <Heading fontSize={24} color="white" m="unset">
            Fml Web
          </Heading>
        </Box>
      </Box>
      <Box width={680} margin="0 auto">
        <Text>
          <Link href="https://github.com/sosukesuzuki/fml">Fml</Link> is a toy
          regular expression engine written in C.
        </Text>
        <Suspense fallback={<div>Loading...</div>}>
          <FmlTable />
        </Suspense>
      </Box>
    </Box>
  );
}
