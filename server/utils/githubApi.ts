import type { NitroFetchOptions, NitroFetchRequest } from "nitropack";

export async function requestGithubApi<T>(url: string, opts?: NitroFetchOptions<NitroFetchRequest>) {
  const fullUrl = url.startsWith("/") ? `https://api.github.com${url}` : url;
  return await $fetch<T>(
    fullUrl,
    {
      headers: {
        Accept: "application/vnd.github+json",
        Authorization: `Bearer ${import.meta.env.GITHUB_TOKEN}`,
      },
      ...opts,
    },
  );
}
