import { inputInfoParser } from "~/type";

const parser = z.object({
  class_id: z.number(),
  password: z.string().length(32),
  info: inputInfoParser,
});

export default defineEventHandler(async (e) => {
  const parsed = parser.safeParse(await readBody(e));
  if (!parsed.success)
    return createZodErrResp(parsed.error);

  const { class_id, password, info } = parsed.data;
  if (!await validatePassword(class_id, password))
    return createResp(null, 401, "未登录");

  return updateInfo(class_id, info);
});
