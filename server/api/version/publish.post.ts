import process from "node:process";
import { fetchLatest } from "gh-release-fetch";

const partsParser = z.object({
  token: z.string(),
  version: z.string().regex(/v(\d+\.){2}\d+/),
});

const file_name = "class-system-display_windows-x86_64.zip";

export default defineEventHandler(async (e) => {
  const parsed = partsParser.safeParse(await readBody(e));
  if (!parsed.success)
    return createZodErrResp(parsed.error);

  const { token, version } = parsed.data;

  if (token !== process.env.PUBLISH_TOKEN)
    return createResp(null, 401, "Token 错误！");

  await fetchLatest(
    {
      repository: "bili9blood/class-system",
      package: file_name,
      destination: "",
      version,
      extract: false,
    },
  );

  const form_data = new FormData();
  form_data.append("file", new File([file_name], file_name));

  const res = await fetch(`https://upload.kstore.space/upload/0?access_token=${token}`, { body: form_data });
  if (res.status !== 200)
    return createResp(null, 500, "上传文件失败！");

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
