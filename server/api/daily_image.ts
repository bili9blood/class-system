const imgArchiveParser = z.object({
  images: z.tuple([
    z.object({
      url: z.string().min(1),
    }),
  ]),
});
export default defineEventHandler(async () => {
  const archive = await $fetch("https://cn.bing.com/HPImageArchive.aspx?format=js&n=1");

  const parsed = imgArchiveParser.safeParse(archive);
  if (!parsed.success)
    return createResp("", 500, "Bing API 请求错误");
  const { url } = parsed.data.images[0];
  return createResp(`https://cn.bing.com${url}`);
});
