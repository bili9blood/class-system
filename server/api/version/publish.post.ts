import fs from "node:fs/promises";

const partsParser = z.tuple([
  z.object({
    name: z.string().regex(/v(\d+\.){2}\d+/),
    filename: z.string().endsWith("_windows-x86_64.zip"),
    data: z.any(),
  }),
],
);

export default defineEventHandler(async (e) => {
  const parts = await readMultipartFormData(e);
  const parsed = partsParser.safeParse(parts);
  if (!parsed.success)
    return createZodErrResp(parsed.error);

  fs.writeFile("./latest.ver.local", parsed.data[0].name);
  fs.writeFile("./latest.zip.local", parsed.data[0].data);
  return createResp(null, 200);
});
