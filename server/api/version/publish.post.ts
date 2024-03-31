import process from "node:process";

const partsParser = z.object({
  token: z.string(),
  version: z.string().regex(/v(\d+\.){2}\d+/),
});

export default defineEventHandler(async (e) => {
  const parsed = partsParser.safeParse(await readBody(e));
  if (!parsed.success)
    return createZodErrResp(parsed.error);

  const { token, version } = parsed.data;

  if (token !== process.env.PUBLISH_TOKEN)
    return createResp(null, 401, "Token 错误！");

  const db = useDatabase();
  try {
    await db.key_value.update({
      where: { key: "latest_ver" },
      data: { value: version },
    });
  }
  catch { return createResp(null, 500, "数据库错误！"); }

  return createResp(null, 200);
});
