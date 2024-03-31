export default defineEventHandler(async () => {
  try {
    const db = useDatabase();
    const { value: version } = await db.key_value.findUniqueOrThrow({ where: { key: "latest_ver" } });
    const { value: url } = await db.key_value.findUniqueOrThrow({ where: { key: "latest_url" } });
    return createResp({ version, url });
  }
  catch (e) { return createResp(null, 500, "无最新版本"); }
});
