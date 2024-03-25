export async function validatePassword(class_id: number, password: string) {
  const res = await $fetch("/api/login", { method: "post", body: { class_id, password } });

  return res.code === 200;
}
