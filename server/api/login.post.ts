import { Md5 } from "ts-md5";

const parser = z.object({
  class_id: z.number(),
  password: z.string().length(32),
});

function hashPwd(password: string) {
  const m = new Md5();
  m.appendStr(password);
  m.appendStr(moment().format("YYYYMMDD"));
  return m.end() as string;
}

export default defineEventHandler(async (e) => {
  const parsed = parser.safeParse(await readBody(e));
  if (!parsed.success)
    return createZodErrResp(parsed.error);

  const { class_id, password: inputed_pwd } = parsed.data;

  const find_res = await useDatabase().class_.findUnique(
    { where: { id: class_id }, select: { man_password: true } },
  );

  if (!find_res)
    return createResp(null, 404, "班级不存在");

  if (inputed_pwd.toLowerCase() === hashPwd(find_res.man_password))
    return createResp(null, 200);
  else
    return createResp(null, 401, "密码错误");
});
