import type { Info } from "~/type";

const parser = z.object({
  class_id: z.number(),
  long: z.boolean().or(z.undefined()),
});

export default defineEventHandler(async (e) => {
  const parsed = parser.safeParse(await readBody(e));
  if (!parsed.success)
    return createZodErrResp(parsed.error);

  const { class_id, long } = parsed.data;

  if (!long)
    return createResp(await getInfo(class_id));

  const res = await Promise.race([
    new Promise<undefined>(r => setTimeout(r, 1000 * 60)),
    observeInfo(class_id),
  ]) as Info | undefined;
  if (res === undefined)
    return createResp(await getInfo(class_id), 304, "无改变");
  else
    return createResp(res);
});
