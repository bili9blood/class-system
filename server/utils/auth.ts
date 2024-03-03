export async function validatePassword(class_id: number, password: string) {
  const res = await $fetch<string>("/api/login", { method: "post", body: { class_id, password } });

  return JSON.parse(res).code === 200;
}
