import { Box, Heading } from "@kuma-ui/core";
import { Suspense } from "react";
import FmlTable from "./FmlTable";

export default function App() {
  return (
    <div>
      <Box p={4} bg="black">
        <Heading color="white" m="unset">
          Fml Web
        </Heading>
      </Box>
      <Suspense fallback={<div>Loading...</div>}>
        <FmlTable />
      </Suspense>
    </div>
  );
}
