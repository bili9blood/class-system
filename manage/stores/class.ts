import { acceptHMRUpdate, defineStore } from "pinia";
import { Notify } from "quasar";
import { Md5 } from "ts-md5";

export const useClassStore = defineStore("user", () => {
  const class_id = ref(0);
  const password = ref("");

  async function login(_class_id: number, _password: string) {
    const hashed_password = Md5.hashStr(_password + moment().format("YYYYMMDD")).toString();
    const result = await $fetch("/api/login", {
      body: {
        class_id: _class_id,
        password: hashed_password,
      },
      method: "POST",
    });

    if (result.code !== 200) {
      Notify.create({
        message: `登录失败： ${result.message}`,
        color: "negative",
      });
      return false;
    }
    class_id.value = _class_id;
    password.value = hashed_password;
    return true;
  }

  return {
    class_id,
    password,

    login,
  };
});

if (import.meta.hot)
  import.meta.hot.accept(acceptHMRUpdate(useClassStore, import.meta.hot));
