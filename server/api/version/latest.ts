import fs from "node:fs/promises";

export default defineEventHandler(async () => {
  try {
    return createResp(
      new TextDecoder().decode(
        await fs.readFile("./latest.ver.local"),
      ),
    );
  }
  catch (e) { return createResp(null, 500, "无最新版本"); }
});
