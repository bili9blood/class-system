import type { NavItem } from "@nuxt/content/types";

export function RemoveDuplicatedContentNav(navigation: NavItem[]): NavItem[] {
  const path_set = new Set<string>();

  const EnumNavigation = (item: NavItem) => {
    if (path_set.has(item._path))
      return false;
    path_set.add(item._path);

    if (item.children)
      item.children = item.children.filter(EnumNavigation);

    return true;
  };

  const cloned = useCloned(navigation).cloned.value;
  return cloned.filter(EnumNavigation);
}
