import fs from "node:fs/promises";

export default defineEventHandler(async () => {
  try {
    return await fs.readFile("./latest.zip.local");
  }
  catch (e) { return createResp(null, 500, "无最新版本"); }
});
