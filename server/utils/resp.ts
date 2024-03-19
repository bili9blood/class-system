import type { ZodError } from "zod";

export function createResp<T>(data: T, code: number = 200, message: string = "成功") {
  return { data, code, message };
}

export function createZodErrResp(err: ZodError) {
  return createResp(null, 400, `参数错误: ${err.message.replace(/(\n| )/g, "")}`);
}
